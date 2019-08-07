#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("### GETGRNAM ###\n");
	struct group *grp;
	int n, m;

	grp = getgrnam("adm");
	printf("Group Name : %s\n", grp->gr_name);
	printf("GID : %d\n", (int)grp->gr_gid);

	n = 0;
	printf("Members : ");
	while (grp->gr_mem[n] != NULL)
		printf("%s ", grp->gr_mem[n++]);
	printf("\n");

	printf("\n### GET GRENT ###\n");
	for (n = 0; n<10; n++){
		grp = getgrent();
		printf("Group Name ; %s, GID : %d ", grp->gr_name, (int)grp->gr_gid);

		m = 0;
		printf("Members : ");
		while (grp->gr_mem[m] != NULL)
			printf("%s ", grp->gr_mem[m++]);
		printf("\n");
	}

	return 0;
}
