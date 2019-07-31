#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 50

int main(int argc, char* argv[]){
	if (argc != 2){
		printf("Usage : %s <DIR>\n", argv[0]);
		exit(1);
	}
	DIR *dp;
	struct dirent *dent;
	struct stat sbuf;
	char path[BUFSIZE], path_file[BUFSIZE], tmp_buf[BUFSIZE], mod[3];
	FILE *fp1, *fp2;

	strcpy(path, argv[1]);

	if (access("tmp", F_OK) == -1 && mkdir("tmp", 0755) == -1){
		perror("make dir tmp : ");
		exit(1);
	}
	if (access("report", F_OK) == -1 && mkdir("report", 0755) == -1){
		perror("make dir report : ");
		exit(1);
	}

	if ((dp = opendir(path)) == NULL){
		perror("Open Dir : ");
		exit(1);
	}

	if ((fp1 = fopen("tmp/dirlist.lst", "w+")) == NULL){
		printf("file open error\n");
		exit(1);
	}

	while ((dent = readdir(dp))){
		sprintf(path_file, "%s/%s", path, dent->d_name);
		stat(path_file, &sbuf);

		strcpy(mod, "---");

		if ((sbuf.st_mode & S_IRWXO) != S_IRWXO){
			if ((sbuf.st_mode & S_IROTH) != 0)
				mod[0] = 'r';
			if ((sbuf.st_mode & S_IWOTH) != 0)
				mod[1] = 'w';
			if ((sbuf.st_mode & S_IXOTH) != 0)
				mod[2] = 'x';
			fprintf(fp1, "%s : %s\n", dent->d_name, mod);
		}
	}
	fseek(fp1, 0, SEEK_SET);

	if ((fp2 = fopen("report/dirlist.lst", "w+")) == NULL){
		printf("File open Error\n");
		exit(1);
	}

	while (fgets(tmp_buf, BUFSIZE, fp1)){
		fputs(tmp_buf, fp2);
	}

	fclose(fp1);
	fclose(fp2);

	unlink("tmp/dirlist.lst");

	if (rmdir("tmp") == -1){
		perror("rmdir");
		exit(1);
	}

	return 0;
}
