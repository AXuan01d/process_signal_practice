//alarm()可设置定时器　　超时可向进程发送SIGALRM信号
//alarm(0) 取消定时器
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_func(int signo){
	printf("alarm time out\n");
	alarm(5);
}

int main(void){
	if(signal(SIGALRM, sig_func) == SIG_ERR){
		perror("SIGALRM error");
	}
	alarm(5);
	printf("process start run\n");
	int i = 20;
	while(i--){
		printf("%d\n",20-i);
		sleep(1);
		if(i==4)
			alarm(0);
	}
	printf("process ended\n");
	return 0;
}	
