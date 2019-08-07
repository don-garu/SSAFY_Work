#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mqueue.h"

int main(){
	pid_t pid;
	MSG mbuf;
	int msqid, n;
	char buf[MSGSIZE];
	key_t key;

	struct stat sbuf;

	key = MSQKEY;
	msqid = msgget(key, IPC_CREAT | 0666);
	if (msqid == -1){
		perror("msgget");
		return -1;
	}

	if ((pid = fork()) == -1){
		perror("fork");
		return -1;
	}

	while (1){
		if (pid > 0){
			printf("Input File Name : ");
			scanf("%s", buf);
			mbuf.mtype = 1;
			strcpy(mbuf.mtext, buf);

			if (msgsnd(msqid, (void*)&mbuf, MSGSIZE, IPC_NOWAIT) == -1){
				perror("msgsnd");
				exit(1);
			}
			usleep(1000);
			if (strcmp(mbuf.mtext, "Q") == 0){
				wait(&n);
				break;
			}
		}
		else if (pid == 0){
			n = msgrcv(msqid, &mbuf, MSGSIZE, 0, 0);
			printf("Received File Name : %s\n", mbuf.mtext);

			if (strcmp(mbuf.mtext, "Q") == 0){
				exit(1);
			}

			if (access(mbuf.mtext, F_OK) == -1){
				perror("access");
				continue;
			}

			stat(mbuf.mtext, &sbuf);

			printf("[C] File Name : %s\n", mbuf.mtext);
			printf("[C] Inode : %d\n", (int)sbuf.st_ino);
			printf("[C] Mode : %o\n", (unsigned int)sbuf.st_mode);
			printf("[C] UID : %d\n", (int)sbuf.st_ino);
		}
	}
	printf("Delete Msg Queue\n");
	if (msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL) < 0){
		perror("msgctl");
		return -1;
	}
	return 0;
}
