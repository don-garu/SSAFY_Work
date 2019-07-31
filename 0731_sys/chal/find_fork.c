#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define BUFSIZE 30

int main(int argc, char ** argv){
	if (argc != 2){
		printf("Usage : %s <DIR>\n", argv[0]);
		exit(1);
	}

	DIR* dp;
	struct dirent *dent;
	struct stat sbuf;
	
	int fd[2];
	char buf[BUFSIZE], dir[BUFSIZE], file[BUFSIZE];
	pid_t pid;
	int status;

	strcpy(dir, argv[1]);
	if (access(dir, F_OK) == -1){
		perror("Access");
		exit(1);
	}

	if ((dp = opendir(dir)) == NULL){
		perror("Open Dir");
		exit(1);
	}

	if (pipe(fd) == -1){
		perror("pipe");
		exit(1);
	}
	memset(buf, 0, sizeof(buf));

	pid = fork();
	if (pid < 0){
		perror("fork");
		exit(1);
	}
	if (pid == 0){
		int flag = 0;
		while (1){
			read(fd[0], buf, BUFSIZE);
			if (strcmp(buf, "Q") == 0){
				exit(1);
			}
		//	printf("[C] %s\n", buf);
			flag = 0;
			rewinddir(dp);
			while ((dent = readdir(dp))) {
				if (strcmp(dent->d_name, buf) == 0){
					printf("\n[C] Find File!\n");
					sprintf(file, "%s/%s", dir, dent->d_name);
					stat(file, &sbuf);

					printf("[C] File name : %s\n", dent->d_name);
					printf("[C] Inode : %d\n", (int)sbuf.st_ino);
					printf("[C] Mode : %o\n", (unsigned int)sbuf.st_mode);
					printf("[C] UID : %d\n", (int)sbuf.st_ino);
					flag = 1;
					break;
				}
			}
			if (!flag)
				printf("[C] Cannot find File\n");
		}
	}
	else if (pid > 0){
		while (1){
			printf("\nInput File Name \"%s\" : ", dir);
			scanf("%s", buf);
			write(fd[1], buf, BUFSIZE);
			if (strcmp(buf, "Q") == 0){
				wait(&status);
				break;
			}
			usleep(100000);
		}
	}
	printf("Process Terminated\n");
}
