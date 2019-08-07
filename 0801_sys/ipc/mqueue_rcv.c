#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MSGSIZE 50

typedef struct {
	long mtype;
	char mtext[MSGSIZE];
}MSG;

int main(){
	MSG rcv_msg;
	int msqid, len;
	key_t key;

	key = ftok("keyfile", 1);
	if ((msqid = msgget(key, 0)) < 0){
		perror("msgget");
		exit(1);
	}

	len = msgrcv(msqid, &rcv_msg, MSGSIZE, 0, 0);
	printf("Received Msg = %sLen = %d\n", rcv_msg.mtext, len);

	return 0;
}
