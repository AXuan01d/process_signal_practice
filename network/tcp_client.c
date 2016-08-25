#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

const int port = 12345;
const char* ipaddr = "192.168.1.209";

int main(void){

	int fd;
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("socket create error");
	printf("client: socket created\n");

	struct sockaddr_in  serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;

	//主机字节序改网络字节序
	//host to network
	serveraddr.sin_port = htons(port);
	//pointer to network
	inet_pton(AF_INET, ipaddr, &serveraddr.sin_addr.s_addr);
	//调用connect指定服务器的ip
	if(connect(fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
		perror("connect error");
	printf("client: connect OK\n");

	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	size_t size;
	if((size = read(fd, buffer, sizeof(buffer))) < 0)
		perror("read error");
	printf("client read content: %s", buffer);

	close(fd);

	return 0;
}
