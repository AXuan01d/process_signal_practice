#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>

int main(int argc, char* argv[]){
	int key = atoi(argv[1]);
	int msq_id;
	if( (msq_id = msgget(key, IPC_CREAT|IPC_EXCL)) < 0 ){
		perror("msgget error");
	}
	printf("message queue id : %d\n", msq_id);
	return 0;
}
