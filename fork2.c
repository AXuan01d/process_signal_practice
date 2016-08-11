//  父进程 子进程的执行策略由系统决定
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
	else if(pid > 0 ){
		int n = 20;
		while(--n){
		printf("parents process  pid = %d %d %d\n",getpid(), getppid(), pid);
		sleep(1);
		}
	
	}
	else{
		int n = 20;
		while(--n){
		printf("children process  pid = %d %d %d\n",getpid(), getppid(), pid);
		sleep(1);
		}
	
	}
	sleep(1);
	exit(0);
	return 0;
}
