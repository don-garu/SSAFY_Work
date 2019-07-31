#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(){
	pid_t pid, ppid;
	int status = 0;

	pid = fork();
	if (pid > 0){
		pid = getpid();
		printf("[Parent %d] Waiting...\n", pid);
		wait(&status);
		status &= 0xff00;
		status = status >> 8;
		printf("[Parent] Status : %d\n", status);
	}
	else if (pid == 0){
		pid = getpid();
		ppid = getppid();
		printf("[Child %d] Parent : %d\n", pid, ppid);
		sleep(5);
		printf("[Child %d] Bye!\n", pid);
		exit(123);
	}
	else {
		printf("Fail to fork child process\n");
	}

	printf("Bye Bye!\n");
	return 0;
}
