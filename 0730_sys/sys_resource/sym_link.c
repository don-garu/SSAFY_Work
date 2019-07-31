#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 30

int main(){
	char str_buf[BUFSIZE];
	struct stat buf;

	int n;

	printf("1. stat : test.txt ---\n");
	stat("test.txt", &buf);
	printf("test.txt : Link Count = %d\n", (int)buf.st_nlink);
	printf("test.txt : Inode = %d\n", (int)buf.st_ino);

	printf("2. stat : test.sln ---\n");
	stat("test.sln", &buf);
	printf("test.sln : Link Count = %d\n", (int)buf.st_nlink);
	printf("test.sln : Inode = %d\n", (int)buf.st_ino);

	printf("3. lstat : test.sln ---\n");
	lstat("test.sln", &buf);
	printf("test.sln : Link Count = %d\n", (int)buf.st_nlink);
	printf("test.sln : Inode = %d\n", (int)buf.st_ino);

	n = readlink("test.sln", str_buf, BUFSIZE);
	if (n == -1){
		perror("Read Link");
		exit(1);
	}

	str_buf[n] = '\0';
	printf("\ntest.sln : READLINK = %s\n", str_buf);

	return 0;
}
