#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t p1, p2;
	int status;

	p1 = fork();
	if (p1 > 0)
		p2 = fork();

	if (p1 > 0 && p2 > 0){
		waitpid(p2, &status, 0);
		printf("[Parent] child 2 exit : %d\n", WEXITSTATUS(status));

		waitpid(p1, &status, 0);
		printf("[Parent] child 1 exit : %d\n", WEXITSTATUS(status));
	}
	else if (p1 > 0 && p2 == 0){
		printf("[Child2] %d : Started\n", getpid());
		sleep(1);
		printf("[Child2] %d : end\n", getpid());
		exit(2);
	}
	else if (p1 == 0){
		printf("[Child1] %d : Started\n", getpid());
		sleep(1);
		printf("[Child1] %d : end\n", getpid());
		exit(1);
	}

	printf("Main process exit\n");
	return 0;
}
