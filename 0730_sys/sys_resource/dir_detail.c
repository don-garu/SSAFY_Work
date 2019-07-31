#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 30

int main(){
	DIR *dp;
	struct dirent *dent;
	struct stat sbuf;
	char path[BUFSIZE];

	printf("Input Directory Path : ");
	scanf("%s", path);

	if (access(path, F_OK) == -1){
		perror("Path : ");
		exit(1);
	}

	if ((dp = opendir(path)) == NULL){
		perror("open dir : ");
		exit(1);
	}

	while ((dent = readdir(dp))) {
		if (dent->d_name[0] == '.')
			continue;
		else
			break;
	}
	sprintf(path, "%s/%s", path, dent->d_name);
	stat(path, &sbuf);

	printf("Name : %s\n", dent->d_name);
	printf("Inode(dirent) : %d\n", (int)dent->d_ino);
	printf("Inode(stat) : %d\n", (int)sbuf.st_ino);
	printf("Mode : %o\n", (unsigned int)sbuf.st_mode);
	printf("UID : %d\n", (int)sbuf.st_uid);

	closedir(dp);

	return 0;
}
