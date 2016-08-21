#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
typedef struct{
	long type;
	int v;
	char ch[4];
}msg;
int main(int argc, char* argv[]){
	int key = atoi(argv[1]);
	int msq_id = msgget(key, 0777);
	msg m[6];
	m[0] = (msg)(msg){1, 0, "000"};
	m[1] = (msg){2, 100, "abc"};
	m[2] = (msg){1, 200, "abc"};
	m[3] = (msg){3, 300, "123"};
	m[4] = (msg){3, 400, "456"};
	m[5] = (msg){2, 500, "abc"};
	int i;
	for(i = 0; i <= 6; ++i){
		if(msgsnd(msq_id, &m[i], sizeof(m[i])-sizeof(long), IPC_NOWAIT) < 0)
			perror("msgsnd error");
	}
	printf("send finish\n");
	return 0;
}
