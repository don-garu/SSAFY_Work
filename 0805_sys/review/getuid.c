#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	uid_t uid, euid;
	char *name, *cname;

	uid = getuid();
	euid = geteuid();

	name = getlogin();
	cname = cuserid(name);

	printf("Login Name = %s, %s UID = %d, EUID = %d\n", name, cname, (int)uid, (int)euid);

	return 0;
}
