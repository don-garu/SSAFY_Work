#include <sys/sysinfo.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	struct sysinfo sys;

	if (sysinfo(&sys) == -1){
		perror("sysinfo");
		exit(1);
	}

	printf("Uptime : %ld\n", sys.uptime);

	return 0;
}
