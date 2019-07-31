#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	pid_t pid;
	char filename[64];
	int n;

	printf("\n");
	for (n = 1; n < argc; n++){
		strcpy(filename, argv[n]);
		printf("Run \"wc %s\"\n", filename);
		pid = fork();
		if (pid == 0){
			execlp("wc", "wc", filename, NULL);
			exit(1);
		}
		usleep(100000);
	}
	printf("End\n");
	return 0;
}
