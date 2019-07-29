#include <sys/types.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern int errno;

int main(){
	int fd;
	mode_t mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	fd = open("mytest.txt", O_CREAT, mode);
	if (fd == -1){
		perror("File Create Error");
		printf("Err no = %d\n", errno);
		exit(1);
	}
	printf("mytest.txt : fd = %d\n", fd);
	close(fd);

	return 0;
}
