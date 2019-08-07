#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	key_t key;
	int msqid;

	//key = ftok("keyfile", 1);
	key = 34856;
	msqid = msgget(key, 0666);
	if (msqid == -1){
		perror("msgget");
		exit(1);
	}

	printf("Before IPC_RMID\n");
	system("ipcs -q");
	msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
	printf("After IPC_RMID\n");
	system("ipcs -q");

	return 0;
}
