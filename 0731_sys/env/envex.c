#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char *envlist[] = {"APPLE=0", "BANANA=1", NULL};
	execle("envex_sub", "envex_sub", NULL, envlist);

	return 0;
}
