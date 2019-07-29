#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd, flags;

	fd = open("mytest.txt", O_RDWR);
	if (fd == -1){
		perror("Open error");
		exit(1);
	}

	if ((flags = fcntl(fd, F_GETFL)) == -1){
		perror("fcntl error");
		exit(1);
	}
	if (write(fd, "Append test\n", 12) != 12)
		perror("Write error");

	flags |= O_APPEND;
	if (fcntl(fd, F_SETFL, flags) == -1){
		perror("fcntl error");
		exit(1);
	}

	if (write(fd, "System Programming\n", 20) != 20)
		perror("Write error");

	close(fd);
	return 0;
}
