#include <utmpx.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#define BUFSIZE 100

int main(){
	struct utmpx *utx;
	char buf[BUFSIZE];
	pid_t pid;
	int status;
	struct stat sbuf;
	DIR *dp;
	struct dirent *dent;

	printf("Login Name Line\n");
	printf("---------------\n");

	while ((utx = getutxent()) != NULL){
		if (utx->ut_type != USER_PROCESS)
			continue;

		printf("%s\t%s\n", utx->ut_user, utx->ut_line);

		// home directory size
		pid = fork();
		sprintf(buf, "/home/%s", utx->ut_user);
		if (pid == 0){
			execlp("du", "du", "-sk", buf, NULL);
		}
		wait(&status);

		stat(buf, &sbuf);
		printf("%s size : %ld\n", buf, sbuf.st_size); // failed (Directory size always 4096?)

		if ((dp = opendir("/home")) == -1){
			perror("opendir");
			return -1;
		}
		while ((dent = readdir(dp))){
			if (strcmp(dent->d_name, utx->ut_user) == 0){
				printf("offset : %d\n", (int)dent->d_ino);
			}
		}
	}

	return 0;
}
