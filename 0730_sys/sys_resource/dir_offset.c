#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	DIR *dp;
	struct dirent *dent;
	char buf[50];

	printf("Input Directory Path : ");
	scanf("%s", buf);

	if ((dp = opendir(buf)) == NULL){
		perror("opendir : ");
		exit(1);
	}

	printf("** Directory Content ** \n");
	printf("Start Offset : %ld\n", telldir(dp));

	while ((dent = readdir(dp))){
		printf("Read : %s\n", dent->d_name);
		printf("Cur Offset : %ld\n", telldir(dp));
	}

	printf("\n** Directory Pointer Rewind **\n");
	rewinddir(dp);
	printf("Cur Offset : %ld\n", telldir(dp));
	printf("\n** Move Directory Pointer ** \n");
	seekdir(dp, 24);
	printf("Cur Offset : %ld\n", telldir(dp));

	dent = readdir(dp);
	printf("Read %s\n", dent->d_name);
	printf("Next Offset : %ld\n", telldir(dp));

	closedir(dp);
	
	return 0;
}
