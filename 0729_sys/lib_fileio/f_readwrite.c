#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 10
#define FILE1 "test.txt"
#define FILE2 "test2.txt"

int main(){
	FILE *rfp, *wfp;
	char buf[BUFSIZE];
	int n;

	if ((rfp = fopen(FILE1, "rb")) == NULL){
		perror("fopen: read file");
		exit(1);
	}
	if ((wfp = fopen(FILE2, "wb")) == NULL){
		perror("fopen: write file");
		exit(1);
	}

	while ((n = fread(buf, sizeof(char)*2, 3, rfp)) > 0){
		fwrite(buf, sizeof(char)*2, n, wfp);
	}

	fclose(rfp);
	fclose(wfp);

	return 0;
}
