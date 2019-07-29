#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *rfp, *wfp;
	int c;

	if ((rfp = fopen("test.txt", "r")) == NULL){
		perror("fopen: test.txt");
		exit(1);
	}
	if ((wfp = fopen("test2.txt", "w")) == NULL){
		perror("fopen: test2.txt");
		exit(1);
	}

	while ((c = fgetc(rfp)) != EOF){
		fputc(c, wfp);
	}

	fclose(rfp);
	fclose(wfp);

	return 0;
}
