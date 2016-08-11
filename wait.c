// wait 可以在子进程终止前 使父进程阻塞
// 并将子进程状态保存在status中
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void out_status(int status){
	printf("status value: %d\n", status);
	
	if(WIFEXITED(status) ){
		printf("normal exit: %d\n", WEXITSTATUS(status) );
	}
	else if(WIFSIGNALED(status) ){
		printf("abnormal term: %d\n", WTERMSIG(status) );
	}
	else if(WIFSTOPPED(status) ){
		printf("stopped sig: %d\n",WSTOPSIG(status) );
	}
	else printf("unknow \n");
	printf("-----------------------\n");
	return;	

}

int main(void){
	int status;
	pid_t pid;
	if(( pid = fork() ) < 0 ){
		perror("fork error");
		exit(1);
	}
	else if( pid == 0 ){
		printf("children  pid: %d  ppid: %d\n", getpid(), getppid() );
		exit(3);
	}
	wait(&status);
	out_status(status);
	
	if(( pid = fork() ) < 0 ){
		perror("fork error");
		exit(1);
	}
	else if( pid == 0 ){
		printf("children  pid: %d  ppid: %d\n", getpid(), getppid() );
		int a = 5 , b = 0;
		int c = a / b;
	}
	wait(&status);
	out_status(status);
	
	if(( pid = fork() ) < 0 ){
		perror("fork error");
		exit(1);
	}
	else if( pid == 0 ){
		printf("children  pid: %d  ppid: %d\n", getpid(), getppid() );
		while(1){  //用kill命令杀死
		}
	}
	wait(&status);
	out_status(status);
	

	return 0;
}

/*
ildren  pid: 6466  ppid: 6465
status value: 768
normal exit: 3
-----------------------
children  pid: 6467  ppid: 6465
status value: 136
abnormal term: 8
-----------------------
children  pid: 6470  ppid: 6465
status value: 9
abnormal term: 9
*/
