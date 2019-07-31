#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 30

int main(){
	FILE* fp;
	int fd;
	char str[BUFSIZE];

	fd = open("test.txt", O_RDONLY);
	if (fd == -1){
		perror("open");
		exit(1);
	}

	fp = fdopen(fd, "r");

	fgets(str, BUFSIZE, fp);
	printf("Read : %s", str);

	fclose(fp);
	close(fd);

	return 0;
}
