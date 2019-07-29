#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd, n;
	off_t start, cur;
	char buf[30];

	fd = open("mytest.txt", O_RDONLY);
	if (fd == -1){
		perror("Open error");
		return 1;
	}

	start = lseek(fd, 0, SEEK_CUR);
	n = read(fd, buf, 10);
	buf[n] = '\0';
	//printf("Offset start = %d, Read Str = %s, n = %d\n", (int)start, buf, n);
	printf("Offset start = %d, n = %d\n", (int)start, n);

	cur = lseek(fd, 0, SEEK_CUR);
	printf("Offset cur = %d\n", (int)cur);

	start = lseek(fd, 5, SEEK_SET);
	n = read(fd, buf, 10);
	buf[n] = '\0';
	//printf("Offset start = %d, Read Str = %s, n = %d\n", (int)start, buf, n);
	printf("Offset start = %d, n = %d\n", (int)start, n);

	cur = lseek(fd, 0, SEEK_CUR);
	printf("Offset cur = %d\n", (int)cur);

	close(fd);

	return 0;
}
