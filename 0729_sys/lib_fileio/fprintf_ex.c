#include <stdlib.h>
#include <stdio.h>

int main(){
	FILE *rfp, *wfp;
	int id, s[4], n;

	if ((rfp = fopen("score.txt", "r")) == NULL){
		perror("fopen: score.txt");
		exit(1);
	}
	if ((wfp = fopen("form_score.txt", "w")) == NULL){
		perror("fopen: form_score.txt");
		exit(1);
	}

	fprintf(wfp, "Student ID\tAverage\n");
	while ((n = fscanf(rfp, "%d %d %d %d %d", &id, s, s+1, s+2, s+3, s+4)) != EOF){
		fprintf(wfp, "%d\t:\t%d\n", id, (s[0] + s[1] + s[2] + s[3]) / 4);
	}

	fclose(rfp);
	fclose(wfp);
	
	return 0;
}
