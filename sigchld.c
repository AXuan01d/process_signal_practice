//signal()函数用于绑定信号到处理函数
// 用ps查看子进程是否为僵尸进程
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int signo){
	printf("child process is dead \n");
	printf("--------------------\n");
	wait(0);   //父进程等待SIGCHLD信号 然后回收子进程
	
}

int main(void){
	
	if(signal(SIGCHLD, sig_handler) == SIG_ERR){
		perror("signal sigtstp error");
	}
	pid_t pid = fork();
	if(pid < 0)
		perror("fork error");
	else if(pid == 0){	
		int i = 0;
		while(i < 5){
			++i;
			printf("pid = %d\n", getpid());
			sleep(1);
		}
	}
	else{
		int i = 0;
		while(i < 20){
			++i;
			printf("pid = %d\n", getpid());
			sleep(1);
		}
	}
	return 0;
}
