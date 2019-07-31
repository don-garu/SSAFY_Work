#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <wait.h>

int main(){
	time_t result;
	pid_t pid;

	int fd, status, i;
	ssize_t nread;
	char buff[32];

	pid = fork();

	if (pid > 0){
		sleep(1);
		wait(&status);
		exit(1);
	}
	else if (pid == 0){
		fd = open("curtime.txt", O_RDWR | O_CREAT, 0644);
		i = 0;
		while (i < 10){
			result = time(NULL);
			strcpy(buff, asctime(localtime(&result)));
			printf("%s", buff);
			write(fd, buff, strlen(buff));
			sleep(2);
			i++;
		}
	}
}
