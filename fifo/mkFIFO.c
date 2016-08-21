#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

const char *fifoname = "./newfifo";

int main(void){

	pid_t pid;
	if(mkfifo(fifoname, 0777) < 0)
		perror("mkfifo error");
	printf("mkfifo ok");
	if( (pid = fork() < 0) ){
		perror("fork error");
	}
	else if(pid == 0){   //子进程

		int fp = open(fifoname, O_WRONLY);
		if(fp < 0)
			perror("child open error");
		char buf[] = "12345678\nabcdefh\n";
		if( write(fp, buf, sizeof(buf)) < 0 )
			perror("write error");
		close(fp);
	}
	else {     // 父进程
		int fp = open(fifoname, O_RDONLY);
		if(fp < 0)
			perror("child open error");
		char buf[45] ;
		if( read(fp, buf, 40) < 0 )
			perror("read error");
		printf("father process get str: %s\n", buf);
		close(fp);
	}
	return 0;
}


