#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* func(void* arg){
	int len = (int)arg;
	while(len > 0){
		printf("control thread id: %lx: %d\n", pthread_self(), len);
		--len;
		usleep(5000);
	}
	return (void*)0;
}

int main(void){
	pthread_t rabbit,turtle;
	if( pthread_create(&rabbit, NULL, func, (void*)50) != 0){
		perror("thread create error");
	}
	if( pthread_create(&turtle, NULL, func, (void*)52) != 0){
		perror("thread create error");
	}
	//调用join阻塞主控线程  等到线程结束继续运行
	pthread_join(rabbit, NULL);
	pthread_join(turtle, NULL);
	//sleep(5);
	printf("control thread id: %lx\n", pthread_self());
	printf("finished!\n");
	return 0;
}
