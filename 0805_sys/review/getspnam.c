#include <shadow.h>
#include <stdio.h>

int main(){
	struct spwd *spw;

	spw = getspnam("jjun");
	printf("Login Name : %s\n", spw->sp_namp);
	printf("Passwd : %s\n", spw->sp_pwdp);
	printf("Last Change : %d\n", spw->sp_lstchg);


	printf("GET SPENT\n");
	for (int n = 0; n<10; n++){
		spw = getspent();
		printf("Login Name : %s, Passwd : %s\n", spw->sp_namp, spw->sp_pwdp);
	}

	return 0;
}
