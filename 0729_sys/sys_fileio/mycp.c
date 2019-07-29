#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int rfd, wfd, n;
	char buf[256];

	if (argc != 3){
		printf("Usage : ./mycp src target\n");
		exit(1);
	}

	rfd = open(argv[1], O_RDONLY);
	if (rfd == -1){
		perror("Open src error");
		return 1;
	}

	wfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (wfd == -1){
		perror("Open target error");
		return 1;
	}
	while ((n = read(rfd, buf, 256)) > 0){
		if (write(wfd, buf, n) != n)
			perror("Write error");
	}
	if (n == -1)
		perror("Read error");

	close(wfd);
	close(rfd);
	
	return 0;
}
