#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

void read_dir(char* path);
void read_file(char* path);

int main(int argc, char * argv []){
	if (argc != 2){
		printf("Usage : %s <DIR>\n", argv[0]);
		exit(1);
	}
	char buf[BUFSIZE];
	strcpy(buf, argv[1]); // copy directory path to buffer
	read_dir(buf);
}

void read_file(char* path){
	FILE* fp;
	char buf[BUFSIZE];
	if ((fp = fopen(path, "r+")) == NULL){
		perror("fopen");
		return;
	}
	while (fgets(buf, BUFSIZE, fp)){
		printf("%s", buf);
	}

	fclose(fp);
}

void read_dir(char* path){
	DIR * dp;
	struct dirent *dent;
	struct stat sbuf;
	char file[BUFSIZE];

	if (access(path, F_OK) == -1){
		perror("dir access");
		return;
	}
	if ((dp = opendir(path)) == NULL){
		perror("dir open");
		return;
	}
	while ((dent = readdir(dp))){
		if (path[strlen(path) - 1] == '/')
			sprintf(file, "%s%s", path, dent->d_name);
		else
			sprintf(file, "%s/%s", path, dent->d_name);

		if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
			continue;
		stat(file, &sbuf);

		if (S_ISDIR(sbuf.st_mode)){
			printf("\n<DIR> %s <%s>\n", dent->d_name, file);
			//read_dir(file);
			continue;
		}
		else if (S_ISREG(sbuf.st_mode)){
			printf("\n<REG>\n");
			printf("File name : %s\n", dent->d_name);
			printf("INode (Drent): %d\n", (int)dent->d_ino);
			printf("Inode (Stat): %d\n", (int)sbuf.st_ino);
			printf("File size : %d\n", (int)sbuf.st_size);
			//read_file(file);
		}
	}
	closedir(dp);
}
