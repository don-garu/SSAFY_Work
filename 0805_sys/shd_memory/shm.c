#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
	int shmid, *cal_num, status;
	pid_t pid;
	void *shd_memory = (void *)0;

	shmid = shmget((key_t)1234, sizeof(int), 0666 | IPC_CREAT);

	if (shmid == -1){
		perror("shmget failed : ");
		exit(0);
	}

	shd_memory = shmat(shmid, (void *)0, 0);
	if (shd_memory == (void *)-1){
		perror("shmat failed : ");
		exit(0);
	}	

	cal_num = (int *)shd_memory;
	if ((pid = fork()) == -1){
		perror("fork error : ");
		exit(1);
	}

	if (pid == 0){
/*		shmid = shmget((key_t)1234, sizeof(int), 0);
		if (shmid == -1){
			perror("shmget failed : ");
			exit(0);
		}
		shd_memory = shmat(shmid, (void *)0, 0666 | IPC_CREAT);
		if (shd_memory == (void *)-1){
			perror("shmat failed : ");
			exit(0);
		}

		cal_num = (int *)shd_memory;*/
		*cal_num = 1;

		while (1){
			if (*cal_num == 10)
				break;
			*cal_num = *cal_num + 1;
			printf("Child %d\n", *cal_num);
			sleep(1);
		}
		exit(1);
	}
	else if (pid > 0){
		while (1){
			sleep(1);
			printf("%d\n", *cal_num);
			if (*cal_num == 10)
				break;
		}
		wait(&status);
	}
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
