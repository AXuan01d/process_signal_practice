//signal()函数用于绑定信号到处理函数
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signo){
	printf("%d, %d occured\n", getpid(), signo);
	printf("--------------------\n");
	return;
}

int main(void){
	
	if(signal(SIGTSTP, sig_handler) == SIG_ERR){
		perror("signal sigtstp error");
	}
	
	if(signal(SIGINT, sig_handler) == SIG_ERR){
		perror("signal sigint error");
	}

	int i = 0;
	while(i < 20){
		++i;
		printf("pid = %d\n", getpid());
		sleep(1);
	}
	return 0;
}
