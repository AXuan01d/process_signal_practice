#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	int res;
	int cnt;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
}node;

void* set(void* arg)
{
	node *r = (node*)arg;
	r->res = 2050;
	printf("set  lock pre\n"); 
	pthread_mutex_lock(&r->mutex);
	printf("set   加锁后\n");
	while(r->cnt<2){
		printf("set < unlock pre\n");		
		pthread_mutex_unlock(&r->mutex);
		printf("set < unlock next\n");
		usleep(1000000);
		printf("set < lock pre\n");		
		pthread_mutex_lock(&r->mutex);
		printf("set < lock next\n");		
	}
	printf("set unlock pre\n");	
	pthread_mutex_unlock(&r->mutex);
	printf("set unlock next\n");		
	pthread_cond_broadcast(&r->cond);
	printf("broadcast next\n");
	return (void*)0;	
}

void* get(void* arg){
	sleep(1);
	node* r = (node*) arg;
	printf(" get %lx lock pre\n", pthread_self());
	pthread_mutex_lock(&r->mutex);
	printf("get %lx lock next\n", pthread_self());
	r->cnt ++;
	printf("get %lx wait pre\n", pthread_self() );
	pthread_cond_wait(&r->cond, &r->mutex);
	printf("get %lx wait next\n", pthread_self() );
	pthread_mutex_unlock(&r->mutex);
	printf("get %lx unlock next\n", pthread_self() );
	printf("%lx thread  the value is %d\n",pthread_self()  , r->res);
	return (void*)0;
}

int main(void){
	node r;
	r.cnt = 0;
	pthread_cond_init(&r.cond, NULL);
	pthread_mutex_init(&r.mutex, NULL);

	pthread_t a,b,c;
	
	if( pthread_create(&a, NULL, &set, (void*)&r) != 0){
		perror("creat_set error");
	}
	if( pthread_create(&b, NULL, &get, (void*)&r) != 0){
		perror("creat_get error");
	}
	if( pthread_create(&c, NULL, &get, (void*)&r) != 0){
		perror("creat_get2 error");
	}
	pthread_join(a, NULL);
	pthread_join(b, NULL);
	pthread_join(c, NULL);
	pthread_cond_destroy(&r.cond);
	pthread_mutex_destroy(&r.mutex);
	return 0;
}
/*
set  lock pre
set   加锁后
set < unlock pre
set < unlock next
 get b639cb70 lock pre
get b639cb70 lock next
get b639cb70 wait pre
 get b6d9db70 lock pre
get b6d9db70 lock next
get b6d9db70 wait pre
set < lock pre
set < lock next
set unlock pre
set unlock next
get b639cb70 wait next
get b639cb70 unlock next
b639cb70 thread  the value is 2050
get b6d9db70 wait next
get b6d9db70 unlock next
b6d9db70 thread  the value is 2050
broadcast next   */
