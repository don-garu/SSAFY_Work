#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	pid_t pid;
	int status;

	if ((pid = fork()) > 0){
		printf("[Parent] PPID: %d\tPID: %d\n", getppid(), getpid());
		printf("[Parent] GID: %d\tPGID: %d\tSID: %d\n", getgid(), getpgrp(), getsid(getpid()));
		printf("[Parnet] getpgid(0): %d\tgetpgid(getpid()): %d\n", getpgid(0), getpgid(getpid()));

		sleep(1);
	}
	else if (pid == 0){
		printf("[Child] Current SID: %d\n", getsid(0));
		printf("[Child] New SID: %d\n", setsid());

		usleep(2000);
	}
	else {
		perror("Fork error");
		return -1;
	}

	return 0;
}
