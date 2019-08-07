#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler(int signum);

int main(){
	struct sigaction act;

	printf("My PID : %d\n", getpid());

	sigfillset(&(act.sa_mask));
	act.sa_handler = handler;

	sigaction(SIGINT, &act, NULL);

	printf("Pause return %d\n", pause());

	return 0;
}

void handler(int signum){
	printf("\nSIGINT catched %d\n\n", signum);
}
