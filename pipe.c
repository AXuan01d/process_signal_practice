#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

char* cmd1[] = {"/bin/cat", "/etc/passwd", NULL};
char* cmd2[] = {"/bin/grep", "root", NULL};

int main(void){
	pid_t pid;
	int i, pfd[2];
	if( pipe(pfd) < 0){
		perror("pipe create error");
	}

	for(i = 0; i < 2; ++i){
		if( (pid = fork()) < 0)
			perror("fork error");
		else if(pid == 0){
			if(i == 0){
				close(pfd[0]);
				if(dup2(pfd[1], STDOUT_FILENO) != STDOUT_FILENO)
					perror("dup2 out error");
				close(pfd[1]);
				if( execvp(cmd1[0], cmd1) < 0)
					perror("execvp error");
				break;
			}
			else if(i == 1){
				close(pfd[1]);
				if(dup2(pfd[0], STDIN_FILENO) != STDIN_FILENO)
					perror("dup2 in error");
				close(pfd[0]);
				if( execvp(cmd2[0], cmd2) < 0)
					perror("execvp2 error");
				break;
			}
		}
		else{
			if(i == 1){
				close(pfd[0]);
				close(pfd[1]);
				wait(0);
				wait(0);
			}
		}
	}
	
	return 0;
}
