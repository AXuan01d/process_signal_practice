#include "pipe_notify.h"

int fd[2];
void init(){
	if(	pipe(fd) < 0)
		perror("pipe create error");
}

void wait_pipe(){
	char ch;
	if(read(fd[0], &ch, 1) < 0) //用read的阻塞 来同步进程
		perror("read error");
}

void notify_pipe(){
	char ch = 'a';
	if(write(fd[1], &ch, 1) != 1)
		perror("write error");	
}

void destroy(){
	close(fd[0]);
	close(fd[1]);
}
