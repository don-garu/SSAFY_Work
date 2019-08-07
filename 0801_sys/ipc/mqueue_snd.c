#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGSIZE 50

typedef struct {
	long mtype;
	char mtext[MSGSIZE];
}MSG;

int main(){
	MSG snd_msg;
	key_t key;
	int msqid;

	key = ftok("keyfile", 1);
	msqid = msgget(key, IPC_CREAT | 0644);
	if (msqid == -1){
		perror("msgget");
		exit(1);
	}

	snd_msg.mtype = 1;
	strcpy(snd_msg.mtext, "Message Queue Test\n");

	if (msgsnd(msqid, (void *)&snd_msg, MSGSIZE, IPC_NOWAIT) == -1){
		perror("msgsnd");
		exit(1);
	}

	return 0;
}
