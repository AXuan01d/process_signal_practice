// fork有两个返回值  子进程返回0   父进程返回子进程号
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void){
	
	printf("pid = %d\n",getpid());

	pid_t pid = fork();
	if(pid < 0 )
		perror("fork error");
	else if(pid > 0 )
		printf("parents process  pid = %d %d %d\n",getpid(), getppid(), pid);
	else
		printf("children process  pid = %d %d %d\n",getpid(), getppid(), pid );
    printf("===================  %d\n",pid);
	sleep(1);
	exit(0);
	return 0;
}
