#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>


void errors(char *msg, int code);
void cleanupaction();

int main(){
	pid_t pid;
	int status;

	pid = fork();
	if (pid > 0){
		printf("[Fork_ex3]\tPPID: %d\tPID: %d\n", getppid(), getpid());
		sleep(1);
		wait(&status);
	}
	else if (pid == 0){
		printf("[Fork_ex3]\tPPID: %d\tPID: %d\n", getppid(), getpid());
		execl("ex_sub", "ex_sub", NULL);
	}
	else {
		printf("Fail to fork\n");
	}
	return 0;
}

void errors(char *msg, int code){
	perror(msg);
	exit(code);
}
void cleanupaction(){
	printf("Clean Up Action\n");
}
