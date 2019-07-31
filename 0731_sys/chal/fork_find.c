#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 30

int main(int argc, char* argv[]){
	if (argc != 2){
		printf("Usage : %s <DIR>\n", argv[0]);
		exit(1);
	}
	DIR* dp;
	struct dirent *dent;
	struct stat sbuf;
	pid_t pid;
	int status;
	char buf[BUFSIZE], dir[BUFSIZE], file[BUFSIZE];

	strcpy(dir, argv[1]);
	if (access(dir, F_OK) == -1){
		perror("Access");
		exit(1);
	}

	if ((dp = opendir(dir)) == NULL){
		perror("open dir");
		exit(1);
	}

	while (1){
		printf("[Parent %d] Input File Name : ", getpid());
		scanf("%s", buf);

		if (strcmp(buf, "Q") == 0)
			break;
		pid = fork();
		if (pid > 0){
			wait(&status);
			if (status >> 8 == 1) 
				printf("[Parent] Complete\n\n");
			else if (status >> 8 == 2)
				printf("[Parent] Failed\n\n");
		}
		else if (pid == 0){
			rewinddir(dp);
			while ((dent = readdir(dp))){
				if (strcmp(dent->d_name, buf) == 0){
					printf("\n[Child %d] Find File!\n", getpid());
					sprintf(file, "%s/%s", dir, dent->d_name);
					stat(file, &sbuf);

					printf("[Child] File name : %s\n", dent->d_name);
					printf("[Child] Inode : %d\n", (int)sbuf.st_ino);
					printf("[Child] UID : %d\n\n", (int)sbuf.st_uid);

					exit(1);
				}
			}
			exit(2);
		}
		else {
			perror("fork error");
			return -1;
		}
	}
}
