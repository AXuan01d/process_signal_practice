//测试信号集的相关函数
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void out_set(sigset_t set){
	int i = 1;
	for(; i < 31; ++i)
		if(sigismember(&set, i))   //信号i是否在集合中
			printf("%d\n", i);
}

void sig_func(int signo){
	printf("start process signal %d\n", signo);
	sigset_t oset;
	if(sigprocmask(SIG_BLOCK, NULL, &oset) < 0){  //取信号屏蔽字
		perror("sigprocmask error\n");
	}
	out_set(oset);
}

int main(void){
	if(signal(SIGUSR1, sig_func) == SIG_ERR){
		perror("signal sigusr1 error");
	}
	if(signal(SIGUSR2, sig_func) == SIG_ERR){
		perror("signal sigusr2 error");
	}

	printf("before signal occured\n");
	sigset_t oset;
	sigemptyset(&oset); //集合置空
	if(sigprocmask(SIG_BLOCK, NULL, &oset) < 0){
		perror("sigprocmask error");
	}
	out_set(oset);
	printf("process %d wait signal\n", getpid());
	pause();
	printf("after signal occured mask:\n");
	sigemptyset(&oset);
	if(sigprocmask(SIG_BLOCK, NULL, &oset) < 0){
		perror("23333");
	}
	out_set(oset);
	printf("ended\n");
	return 0;
}
