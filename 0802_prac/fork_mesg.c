#include <sys/types.h>
#include <sys/msg.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100
#define MSQID 34858

typedef struct {
	long mtype;
	long mtext[BUFSIZE];
}MSG;

int main(){
	pid_t pid;
	int status, msqid;
	char buf[BUFSIZE];
	key_t key;
	MSG mbuf;

	key = MSQID;
	if ((msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666)) == -1){
		perror("msgget");
		return -1;
	}
	if ((pid = fork()) == -1){
		perror("fork");
		return -1;
	}

	while (1){
		if (pid > 0){
			printf("Input Your Msg : ");
			scanf("%s", buf);
			strcpy(mbuf.mtext, buf);
			mbuf.mtype = 1;

			if ((msgsnd(msqid, &mbuf, BUFSIZE, IPC_NOWAIT)) == -1){
				perror("msgsnd");
				return -1;
			}
			if (strcmp(buf, "Q") == 0 || strcmp(buf, "q") == 0){
				wait(&status);
				break;
			}
			usleep(1000);
		}
		else if (pid == 0){
			msgrcv(msqid, &mbuf, BUFSIZE, 0, 0);
			strcpy(buf, mbuf.mtext);

			printf("Received Msg : %s\n", buf);
			if (strcmp(buf, "Q") == 0 || strcmp(buf, "q") == 0){
				exit(1);
			}
		}
	}
	printf("Exit\n");
	if ((msgctl(msqid, IPC_RMID, NULL)) == -1){
		perror("msgctl");
		return -1;
	}
	return 0;
}
