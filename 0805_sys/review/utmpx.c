#include <utmpx.h>
#include <stdio.h>

int main(){
	struct utmpx *utx;

	printf("Login Name Line\n");
	printf("---------------\n");

	while ((utx = getutxent()) != NULL){
		if (utx->ut_type != USER_PROCESS)
			continue;
		printf("%s\t%s\n", utx->ut_user, utx->ut_line);
	}
	return 0;
}
