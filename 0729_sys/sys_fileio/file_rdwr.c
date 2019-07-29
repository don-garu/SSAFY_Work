#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int fd = 0;

	fd = open("mytest.txt", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1){
		perror("Open Error");
		return 1;
	}
	//unlink("mytest.txt");

	char buf[10] = "Hello\n";
	int re = write(fd, buf, 10);

	if (re == 10)
		printf("Write ok\n");
	else
		printf("Write fail\n");

	close(fd);
	return 0;
}
