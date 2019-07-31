#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

int main(){
	printf("Exec ls!\n");

	execl("/bin/ls", "ls", "-l", NULL);

	return 0;
}
