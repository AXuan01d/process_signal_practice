//共享内存不继承
//继承映射后的虚拟地址
#include "pipe_notify.h"
#include <sys/shm.h>
#include <sys/types.h>
typedef struct{
	int v;
	char ch[5];
}node;

int key = 10;
int main(void){
	int shmid;
	if( (shmid = shmget(IPC_PRIVATE, sizeof(node), IPC_CREAT|IPC_EXCL|0777)) < 0 )
		perror("shmget error");
	init();
	node *t = shmat(shmid, 0, 0);      // 映射得到的地址可以继承
	if (t == (node*)-1)
		perror("shmat error");

	int pid = fork();
	if(pid < 0)
		perror("fork error");
	else if(pid == 0){
		wait_pipe();/*
		node *t = shmat(shmid, 0, 0);      // 映射得到的地址可以继承
		if (t == (node*)-1)
			perror("shmat error");*/
		printf("%d %s\n", t->v, t->ch);
		shmdt(t); //子进程解除映射
		shmctl(shmid, IPC_RMID, NULL); //删除共享内存
		destroy();  //删管道
	}
	else {
		/*
		node *t = shmat(shmid, 0, 0);      // 映射得到的地址可以继承
		if (t == (node*)-1)
			perror("shmat error");
			*/
		t->v = 15;
		t->ch[0] ='a';
		t->ch[1] ='b';
		t->ch[2] ='c';
		t->ch[3] ='\0';

		shmdt(t);   //父进程解除映射
		notify_pipe();
		destroy();
		wait(0);
	}
	return 0;
}
