//4个进程的进程扇 创建两个进程组
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
			}
			if( i == 2){
				setpgid(pid,group2);
			}

		}
		else if(pid == 0)
			break;
	}
	printf("pid: %d ppid: %d  pgid: %d\n",getpid(), getppid(), getpgid(0));
	for(i =0 ;i<3; ++i){
		wait(0);
	}
	return 0;
}
/*
pid: 8837 ppid: 8341  pgid: 8837
pid: 8840 ppid: 8837  pgid: 8839
pid: 8839 ppid: 8837  pgid: 8839
pid: 8838 ppid: 8837  pgid: 8837
*/
