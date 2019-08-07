#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 50
int main(){
	int fd1[2], fd2[2];
	int status;
	pid_t pid;
	char buf[BUFSIZE];

	if (pipe(fd1) == -1){
		perror("pipe fd1");
		exit(1);
	}
	if (pipe(fd2) == -1){
		perror("pipe fd2");
		exit(1);
	}
	
	if ((pid = fork()) == -1){
		perror("pipe");
		exit(1);
	}

	for (int i = 0; i<5; i++){
		memset(buf, 0, sizeof(buf));
		if (pid > 0){
			read(fd1[0], buf, BUFSIZE);
			printf("[P] <= %s\n", buf);

			strcat(buf, "\t[P] : Hi");
			write(fd2[1], buf, BUFSIZE);

			usleep(10000);
		}
		else if (pid == 0){
			strcpy(buf, "[C] : Hello");
			write(fd1[1], buf, BUFSIZE);

			read(fd2[0], buf, BUFSIZE);
			printf("[C] <= %s\n", buf);

			usleep(10000);
		}
	}
	if (pid > 0)
		printf("Exit\n");
}
