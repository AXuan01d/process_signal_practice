//exec 切换成功 不会再有返回值
//进程后部分内容不会再执行
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
char *cmd1 = "cat";
char *cmd2 = "/bin/cat";
char *argv1 = "/etc/passwd";
char *argv2 = "/etc/group";
int main(void){
	pid_t pid;
	if( (pid = fork() ) < 0){
		perror("fork error");
		exit(1);
	}
	else if(pid == 0){
		if ( execl(cmd2 ,cmd1, argv1, argv2, NULL) < 0){  // 子进程进行切换
			perror("execl error");
			exit(1);
		}
		else { 
			printf("------------ return ---------------");  //不执行
		}
	}
	wait(NULL);
	printf("-----------------------\n");
	return 0;
}
