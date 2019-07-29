#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>

extern int errno;

int main(){
	if (access("mytext.txt", F_OK) == -1){
		printf("errno=%d\n", errno);
	}
	return 0;
}
