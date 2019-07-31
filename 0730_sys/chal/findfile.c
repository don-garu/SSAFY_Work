#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 256

int main(int argc, char * argv[]){
	if (argc != 3){
		printf("Usage : %s <DIR> <filename>\n", argv[0]);
		exit(1);
	}

	DIR *dp;
	struct dirent *dent;
	struct stat sbuf;
	char dir_name[BUFSIZE], file_name[BUFSIZE], path[BUFSIZE];

	strcpy(dir_name, argv[1]);
	strcpy(file_name, argv[2]);

	if (access(dir_name, F_OK) == -1){
		perror("Access denied: ");
		exit(1);
	}
	if ((dp = opendir(dir_name)) == NULL){
		perror("OpenDir : ");
		exit(1);
	}

	while ((dent = readdir(dp))){
		if (strcmp(dent->d_name, file_name) == 0){
			sprintf(path, "%s/%s", dir_name, file_name);
			stat(path, &sbuf);

			printf("Name : %s\n", dent->d_name);
			printf("Inode(dirent) : %d\n", (int)dent->d_ino);
			printf("Inode(stat) : %d\n", (int)sbuf.st_ino);
			printf("Mode : %o\n", (unsigned int)sbuf.st_mode);
			printf("UID : %d\n", (int)sbuf.st_uid);
		}
		else
			continue;
	}
	closedir(dp);

	return 0;
}
