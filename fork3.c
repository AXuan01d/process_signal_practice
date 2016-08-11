// 父进程 复制一份(正文段 数据段 堆 栈)给子进程
//此时 两进程 中 同变量的地址（虚拟空间一样）
//但值不一定一样
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
int a;   //全局变量a
int main(void){
	int b;  //变量b
	static c;  //静态变量c
	printf("pid = %d\n",getpid());

	pid_t pid = fork();
	if(pid < 0 )
		perror("fork error");
	else if(pid > 0 ){
		a = 10, b = 10, c = 10;
		printf("parents process  pid = %d %d %d\n",getpid(), getppid(), pid);
		printf("varible address  a: %p  b: %p c: %p\n", &a, &b, &c);
	}
	else{
		a = 20, b = 20, c = 20;
		printf("children process  pid = %d %d %d\n",getpid(), getppid(), pid );
			printf("varible address  a: %p  b: %p c: %p\n", &a, &b, &c);
	}
    printf("===================  %d\n",pid);
	printf("varible value: %d %d %d\n", a, b, c);
	sleep(1);
	exit(0);
	return 0;
}
