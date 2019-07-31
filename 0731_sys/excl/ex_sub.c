#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv){
	printf("[Fork_ex3_sub]\tPPID: %d\tPID: %d\n", getppid(), getpid());

	return 0;
}
