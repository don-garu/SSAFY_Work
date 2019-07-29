#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int fd, fd1, fd2;

	fd = open("mytest.txt", O_RDWR);
	fd1 = open("mytest.txt", O_RDWR);
	fd2 = open("mytest.txt", O_RDWR);
	if (fd == -1 || fd1 == -1 || fd2 == -1){
		perror("Excl");
		exit(1);
	}

	printf("mytest.txt : fd = %d\n", fd);
	printf("mytest.txt : fd1 = %d\n", fd1);
	printf("mytest.txt : fd2 = %d\n", fd2);

	close(fd);
	close(fd1);
	close(fd2);

	return 0;
}
