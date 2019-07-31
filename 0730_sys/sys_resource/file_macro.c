#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	struct stat buf;
	char file_name[256];

	printf("Input File name : ");
	scanf("%s", file_name);

	if (access(file_name, F_OK) == -1){
		perror("Open: ");
		exit(1);
	}

	stat(file_name, &buf);

	printf("Mode = %o (Hexadecimal : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

	if (S_ISFIFO(buf.st_mode)) printf("test.txt : FIFO\n");
	if (S_ISDIR(buf.st_mode)) printf("test.txt : Directory\n");
	if (S_ISREG(buf.st_mode)) printf("test.txt : Regular File\n");

	return 0;
}
