#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	struct stat buf;
	char file_name[256];

	printf("Input File Name : ");
	scanf("%s", file_name);

	if (access(file_name, F_OK) == -1){
		perror("Open File: ");
		exit(1);
	}

	stat(file_name, &buf);

	printf("Inode = %d\n", (int)buf.st_ino);
	printf("Mode = %o\n", (unsigned int)buf.st_mode);
	printf("Nlink = %o\n", (unsigned int)buf.st_nlink);
	printf("UID = %d\n", (int)buf.st_uid);
	printf("GID = %d\n", (int)buf.st_gid);
	printf("SIZE = %d\n", (int)buf.st_size);
	printf("Atime = %d\n", (int)buf.st_atime);
	printf("Mtime = %d\n", (int)buf.st_mtime);
	printf("Ctime = %d\n", (int)buf.st_ctime);
	printf("Blksize = %d\n", (int)buf.st_blksize);
	printf("Blocks = %d\n", (int)buf.st_blocks);
//	printf("FStype = %s\n", buf.st_fstype);

	return 0;
}
