// system()函数通过 bash创建子进程 然后调用exec切换实现
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char *cmd1 = "date > s1.txt";
char *cmd2 = "date > s2.txt";

void my_system(const char* cmd){
	pid_t pid;
	if( (pid = fork() ) < 0){
		perror("fork error");
		exit(1);
	}
	else if(pid == 0){
		if(execlp("/bin/bash", "/bin/bash", "-c", cmd, NULL) < 0){
			perror("execlp error");
			exit(1);
		}
	}
	else 
		wait(NULL);
}

int main(void){

	system(cmd1);
	my_system(cmd2);	
	return 0;
}

