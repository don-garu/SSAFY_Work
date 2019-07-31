#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	struct stat buf;
	char file_name[256];
	int kind;

	printf("Input File Name : ");
	scanf("%s", file_name);

	if (access(file_name, F_OK) == -1){
		perror("Open: ");
		exit(1);
	}

	stat(file_name, &buf);

	printf("Mode = %o (Hexadecimal : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

	kind = buf.st_mode & S_IFMT;
	printf("Kind = %x\n", kind);

	switch (kind){
		case S_IFIFO:
			printf("%s : FIFO\n", file_name);
			break;
		case S_IFDIR:
			printf("%s : Directory\n", file_name);
			break;
		case S_IFREG:
			printf("%s : Regular File\n", file_name);
			break;
	}
	return 0;
}
