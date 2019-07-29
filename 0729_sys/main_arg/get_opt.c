#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

extern char *optarg;
extern int optind;

int main(int argc, char* argv[]){
	int n;
	
	printf("Current Optind : %d\n", optind);

	while ((n = getopt(argc, argv, "abc:")) != -1){
		switch (n){
			case 'a':
				printf("Option : a\n");
				break;
			case 'b':
				printf("Option : b\n");
				break;
			case 'c':
				printf("Option : c, Argument = %s\n", optarg);
				break;
		}
		printf("Next Optind : %d\n", optind);
	}

	return 0;
}
