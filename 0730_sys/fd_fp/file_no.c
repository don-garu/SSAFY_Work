#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 30

int main(){
	FILE *fp;
	int fd, n;
	char str[BUFSIZE];

	fp = fopen("test.txt", "r");

	if (fp == NULL){
		perror("fopen");
		exit(1);
	}

	fd = fileno(fp);
	printf("fd : %d\n", fd);

	n = read(fd, str, BUFSIZE);
	str[n] = '\0';
	printf("Read : %s\n", str);

	close(fd);
	fclose(fp);

	return 0;
}
