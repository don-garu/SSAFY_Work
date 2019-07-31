#include <sys/errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int errno;

int main(){
	int per;
	char *err;
	if (access("test.txt", F_OK) == -1 && errno == ENOENT){
		err = strerror(errno);
		printf("test.txt: %s\n", err);
	}

	per = access("test.txt", R_OK);
	if (per == 0)
		printf("test.txt: Read permission is permitted.\n");
	else if (per == -1 && errno == EACCES){
		err = strerror(errno);
		printf("test.txt: %s.\n", err);
	}

	return 0;
}
