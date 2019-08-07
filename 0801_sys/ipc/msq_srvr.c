#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

	if ((msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666)) < 0){
		perror("msgget");
		return -1;
	}
	while ((n = msgrcv(msqid, &mbuf, MSQSIZE, 0, 0)) > 0){
		switch (mbuf.mtype){
			case 1:
				write(1, mbuf.mtext, n);
				break;
			case 2:
				goto out;
		}
	}
out:
	if (msgctl(msqid, IPC_RMID, (struct msqid_ds*)0) < 0){
		perror("msgctl");
		return -1;
	}
	return 0;
}
