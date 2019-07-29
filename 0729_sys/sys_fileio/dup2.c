#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char *fname = "test.txt";
	int fd;
	if ((fd = creat(fname, 0666)) < 0){
		perror("create( )");
		return -1;
	}
	printf("First printf is on the screen.\n");
	fflush(stdout);
	dup2(fd, 1);
	printf("Second printf is in this file. %d\n", fd);
	close(fd);
	return 0;
}
