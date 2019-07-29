#include <sys/errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	if (access("mytext.txt", R_OK) == -1){
		perror("Can't find mytext.txt");
		exit(1);
	}
	return 0;
}
