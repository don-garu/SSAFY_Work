#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFSIZE 100
#define KEYID 34020

int main(){
	int shmid, status;
	pid_t pid;
	void *shd_memory = (void *)0;
	char *buf;
	struct stat sbuf;

	if ((shmid = shmget((key_t)KEYID, sizeof(BUFSIZE), 0666 | IPC_CREAT)) == -1){
		perror("shmget failed : ");
		exit(0);
	}
	shd_memory = shmat(shmid, (void*)0, 0);
	if (shd_memory == (void *)-1){
		perror("shmat failed : ");
		exit(0);
	}
	buf = (char *)shd_memory;
	
	if ((pid = fork()) == -1){
		perror("fork error : ");
		exit(1);
	}

	if (pid == 0){
		while (1){
			if (strlen(buf)){
				if (strcmp(buf, "Q") == 0){
					printf("> Bye Bye..\n");
					break;
				}
				if (access(buf, F_OK) == -1){
					perror("access denied : ");
					strcpy(buf, "");
					continue;
				}
				printf("> %s\n", buf);
				if (stat(buf, &sbuf) == -1){
					perror("stat error : ");
					continue;
				}

				printf("File name : %s\n", buf);
				printf("Inode : %d\n", (int)sbuf.st_ino);
				printf("Mode : %d\n", (int)sbuf.st_mode);

				strcpy(buf, "");
			}
		}
	}
	else if (pid > 0){
		while (1){
			printf("Input File Name : ");
			scanf("%s", buf);


			if (strcmp(buf, "Q") == 0)
				break;

			usleep(1000);
		}
	}
	if (shmdt(shd_memory) == -1){
		perror("shmdt error : ");
		exit(1);
	}

	if (pid > 0)
		exit(1);

	wait(&status);

	if (shmctl(shmid, IPC_RMID, NULL) == -1){
		perror("shmctl error : ");
		exit(1);
	}
	return 0;
}
