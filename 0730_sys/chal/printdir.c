#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 256

int main(int argc, char * argv[]){
	if (argc == 1){
		printf("Usage : %s <DIR> [-s]\n", argv[0]);
		exit(1);
	}
	if (argc == 3 && strcmp(argv[2], "-s") != 0){
		printf("Usage : %s <DIR> -s\n", argv[0]);
		exit(1);
	}

	DIR *dp;
	struct dirent *dent;
	struct stat sbuf;
	char dir_name[BUFSIZE], path[BUFSIZE];

	strcpy(dir_name, argv[1]);

	if (access(dir_name, F_OK) == -1){
		perror("Access denied: ");
		exit(1);
	}
	if ((dp = opendir(dir_name)) == NULL){
		perror("OpenDir : ");
		exit(1);
	}

	if (argc == 3){
		printf("==========DIR==========\n");
		while ((dent = readdir(dp))){
			if (dent->d_name[0] == '.')
				continue;
			sprintf(path, "%s/%s", dir_name, dent->d_name);
			stat(path, &sbuf);

			if (!(S_ISDIR(sbuf.st_mode)))
				continue;

			printf("Name : %s\n", dent->d_name);
			printf("Inode(dirent) : %d\n", (int)dent->d_ino);
			printf("Inode(stat) : %d\n", (int)sbuf.st_ino);
			printf("Mode : %o\n", (unsigned int)sbuf.st_mode);
			printf("UID : %d\n", (int)sbuf.st_uid);
		}
		rewinddir(dp);
		printf("\n==========REG==========\n");
		while ((dent = readdir(dp))){
			if (dent->d_name[0] == '.')
				continue;
			sprintf(path, "%s/%s", dir_name, dent->d_name);
			stat(path, &sbuf);

			if (S_ISDIR(sbuf.st_mode))
				continue;

			printf("Name : %s\n", dent->d_name);
			printf("Inode(dirent) : %d\n", (int)dent->d_ino);
			printf("Inode(stat) : %d\n", (int)sbuf.st_ino);
			printf("Mode : %o\n", (unsigned int)sbuf.st_mode);
			printf("UID : %d\n", (int)sbuf.st_uid);
		}
	}
	else {
		while ((dent = readdir(dp))){
			if (dent->d_name[0] == '.')
				continue;
			sprintf(path, "%s/%s", dir_name, dent->d_name);
			stat(path, &sbuf);

			printf("Name : %s\n", dent->d_name);
			printf("Inode(dirent) : %d\n", (int)dent->d_ino);
			printf("Inode(stat) : %d\n", (int)sbuf.st_ino);
			printf("Mode : %o\n", (unsigned int)sbuf.st_mode);
			printf("UID : %d\n", (int)sbuf.st_uid);
		}
	}
	closedir(dp);

	return 0;
}
