#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	struct utsname uts;

	if (uname(&uts) == -1){
		perror("uname");
		exit(1);
	}

	printf("OS name\t\t: %s\n", uts.sysname);
	printf("Node name\t: %s\n", uts.nodename);
	printf("Release\t\t: %s\n", uts.release);
	printf("Version\t\t: %s\n", uts.version);
	printf("Machine\t\t: %s\n", uts.machine);

	return 0;
}
