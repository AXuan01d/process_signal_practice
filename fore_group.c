//shell中启动的父进程所在进程组默认为前台进程组
//终端信号（如ctrl+c）只对前台进程组生效
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void){
	pid_t group1 = getpid();
	pid_t group2;
	pid_t pid;
	setpgid(getpid(), group1);
	
	int i;
	for(i = 0; i < 3; ++i){
		if( (pid = fork() ) < 0){
			perror("fork error");
			exit(1);
		}
		else if(pid > 0){
			if( i == 0){
				setpgid(pid, group1);
			}
			if( i == 1 ){
				group2 = pid;
				setpgid(pid, group2);
				tcsetpgrp(0, group2);
			}
			if( i == 2){
				setpgid(pid,group2);
			}

		}
		else if(pid == 0)
			break;
	}
	printf("pid: %d ppid: %d  pgid: %d\n",getpid(), getppid(), getpgid(0));
	pause();
	return 0;
}
