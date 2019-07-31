#include <sys/types.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>

int glob = 6;

int main(){
	int var;
	pid_t pid;
	var = 88;

	printf("Before Vfork[%d]\n", getpid());
	if ((pid = vfork()) < 0){
		perror("Vfork error");
		return -1;
	}
	else if (pid == 0){
		printf("Vfork child[%d]\n", getpid());
		glob++;
		var++;
		_exit(0);
	}

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);

	return 0;
}
