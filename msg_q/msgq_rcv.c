#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
typedef struct{
	long type;
	int v;
	char ch[4];
}msg;
int main(int argc, char*argv[]){
	int key = atoi(argv[1]);
	

	int msq_id = msgget(key, 0777);
    if(msq_id < 0)
		perror("msgget error");
	int type;
	msg t;
	while(1){
		printf("please input msg type\n");
		scanf("%d", &type);
		if(msgrcv(msq_id, &t, sizeof(msg)-sizeof(long), type, IPC_NOWAIT) < 0)
			perror("msgrcv error");
		else
			printf("msgValue: %d msgString: %s\n", t.v, t.ch);
	}
	return 0;
}
