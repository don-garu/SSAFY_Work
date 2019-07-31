#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void cleanupaction();

int main(){
	pid_t pid;
	int i;

	for (size_t i = 0; i<3; i++){
		printf("Before fork [%d]\n", (int)i);
		sleep(1);
	}

	pid = fork();
	if (pid > 0){
		for (size_t i = 0; i<7; i++){
			printf("Parent [%d]\n", (int)i);
			sleep(1);
		}
		atexit(cleanupaction);
	}
	else if (pid == 0){
		for (size_t i = 0; i<5; i++){
			printf("Child[%d]\n", (int)i);
			sleep(1);
			execl("/bin/ls", "ls", "-l", NULL);
		}
	}
	else {
		printf("Fail to fork children\n");
	}

	return 0;
}

void cleanupaction(){
	printf("Clean-Up-Action\n");
}
