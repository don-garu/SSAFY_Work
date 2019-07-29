#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int rfd, wfd, n;
	char buf[10];

	rfd = open("mytest.txt", O_RDONLY | O_CREAT);
	if (rfd == -1){
		perror("Open mytest error");
		return 1;
	}

	wfd = open("mytest2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (wfd == -1){
		perror("Open mytest2 error");
		return 1;
	}
	
	while ((n = read(rfd, buf, 6)) > 0){
		if (write(wfd, buf, n) != n)
			perror("Write error");
	}
	if (n == -1)
		perror("Read error");

	close(rfd);
	close(wfd);

	return 0;
}
