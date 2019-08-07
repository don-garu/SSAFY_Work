#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSQKEY 34856
#define MSQSIZE 32

typedef struct {
	long mtype;
	char mtext[MSQSIZE];
}MSG;

int main(){
	key_t key;
	int n, msqid;
	MSG mbuf;

	key = MSQKEY;

	if ((msqid = msgget(key, 0666)) < 0){
		perror("msgget");
		return -1;
	}
	mbuf.mtype = 1;
	while ((n = read(0, mbuf.mtext, MSQSIZE)) > 0){
		if (msgsnd(msqid, &mbuf, n, 0) < 0){
			perror("msgsnd");
			return -1;
		}
	}
	mbuf.mtype = 2;
	memset(mbuf.mtext, 0, MSQSIZE);
	if (msgsnd(msqid, &mbuf, MSQSIZE, 0) < 0){
		perror("msgsnd");
		return -1;
	}
	return 0;
}
