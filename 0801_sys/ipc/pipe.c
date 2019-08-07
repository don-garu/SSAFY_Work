#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 30

int main(int argc, char * argv[]){
	pid_t pid;
	int status;
	int fd[2];
	char buf[BUFSIZE];

	if ((pipe(fd)) == -1){
		perror("Pipe error");
		exit(1);
	}

	if ((pid = fork()) == -1){
		perror("Fork error");
		exit(1);
	}

	while (1){
		memset(buf, 0, sizeof(buf));
		if (pid > 0){
			printf("Input : ");
			scanf("%s", buf);

			if (strcmp(buf, "Q") == 0){
				wait(&status);
				break;
			}

			write(fd[1], buf, BUFSIZE);
			usleep(10000);
		}
		else if (pid == 0){
			read(fd[0], buf, BUFSIZE);

			if (strcmp(buf, "Q") == 0){
				printf("End Child\n");
				exit(1);
			}

			printf("Output : %s\n", buf);
		}
	}
	printf("Exit\n");
}
