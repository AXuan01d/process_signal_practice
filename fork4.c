//文件io标准库采取全缓存策略
//而缓存区 由堆分配
//所以子进程会复制父进程的 缓存区
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
int a;
int main(void){
	int b;
	static int c;
	printf("pid = %d\n",getpid());

	FILE *fp = fopen("out.txt", "w");
	
   	char* str = "hello world";

	//父进程写入缓存
	fprintf(fp, "str: %s pid: %d   ====", str, getpid());
	

	pid_t pid = fork();
	if(pid < 0 )
		perror("fork error");
	else if(pid > 0 ){
		a = 10, b = 10, c = 10;
		printf("parents process  pid = %d %d %d\n",getpid(), getppid(), pid);
	}
	else{
		a = 20, b = 20, c= 20;
		printf("children process  pid = %d %d %d\n",getpid(), getppid(), pid );
	}
    printf("===================  %d\n",pid);
//	父子进程都写入缓存
	fprintf(fp ,"varible value: %d %d %d\n", a, b, c);

	sleep(1);
	exit(0);
	return 0;
}

/*
out.txt:
str: hello world pid: 5169   ====varible value: 10 10 10
str: hello world pid: 5169   ====varible value: 20 20 20
*/
