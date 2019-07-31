#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE *fp;
	char buf[256];

	if (argc != 2){
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		return -1;
	}

	if ((fp = fopen(argv[1], "a+")) == NULL){
		perror("Fopen error");
		return -1;
	}

	fputs("Input String >> ", stdout);
	fgets(buf, sizeof(buf), stdin);
	fputs(buf, fp);

	puts(buf);
	fclose(fp);

	return 0;
}
