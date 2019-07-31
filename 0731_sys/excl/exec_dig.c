#include <unistd.h>
#include <wait.h>

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
	pid_t pid;
	int i, status;
	char data[64];

	pid = getpid();
	printf("pid : %d\n", pid);
	for (i = 1; i<argc; i++){
		pid = fork();
		if (pid == 0){
			strcpy(data, argv[i]);
			pid = getpid();
			printf("[%d]Exec \"dig %s\"\n", pid, data);
			execlp("dig", "dig", data, NULL);
			exit(1);
		}
		sleep(1);
	}
	for (i = 1; i<argc; i++)
		wait(&status);
	printf("Main End\n");
	return 0;
}
