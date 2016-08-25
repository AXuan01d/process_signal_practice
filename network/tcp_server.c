#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <time.h>
#include <memory.h>
#include <signal.h>

void print(struct sockaddr_in *addr){
	int port2 = ntohs(addr->sin_port);
	char ip[16];
	memset(ip, 0, sizeof(ip));
	inet_ntop(AF_INET, &addr->sin_addr.s_addr, ip, sizeof(ip));
	printf("server: (client address: %s(%d) connected)\n", ip, port2);
}

void do_service(int cfd){
	long t = time(0);
	char* s = ctime(&t);
	size_t size = strlen(s) * sizeof(char);
	if( write(cfd, s, size) != size)
		perror("write error");
}

int fd;
void sig_handler(int sig){
	if(sig == SIGINT){
		close(fd);
		exit(1);
	}
}

int main(void){
	if(signal(SIGINT, sig_handler) == SIG_ERR){
		perror("signal sigint error");
		exit(1);
	}

	//第一步 创建socket 
	//AF_INET: IPV4
	//SOCK_STREAM: tcp
	//0: 默认协议
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("socket create error");
	printf("server: socket created\n");
	
	int on = 1;
	int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	//第二步 调用bind 将socket与地址端口绑定
	struct sockaddr_in  sock_addr;
	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	int port = 12345;
	sock_addr.sin_port = htons(port); //主机字节序转为网络字节序
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
		perror("bind error");
	printf("server: bind OK\n");

	//第三步 调用listen启动监听(指定port监听)
	//通知系统去接受来自客户端的连接请求
	//(将接受到的客户端连接放置到长度为10的队列中)
	if(listen(fd, 10) < 0)
		perror("listen error");
	printf("server: listen OK\n");

	//第四步 调用accept函数从队列中获得一个客户端的请求连接
	//并返回一个客户端的socket文件描述符
	//如果没有客户端连接请求, 到这里会阻塞
	//第二个参数用来获得客户端的地址结构
	int client_fd;
	struct sockaddr new_addr;
	int len = sizeof(new_addr);
	if( (client_fd = accept(fd, &new_addr, &len)) < 0 )
		perror("accept error");
	printf("server: accept  OK\n");
	
	//应道  (读客户端数据, 写数据给客户端)
	print((struct sockaddr_in*)&new_addr);
	do_service(client_fd);

	//关闭socket文件
	close(fd); 
	printf("server: close OK\n");	
	return 0;
}
