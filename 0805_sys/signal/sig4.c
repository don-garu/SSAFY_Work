#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int num;

void int_handle(int signum);

int main(){
	static struct sigaction act;

	act.sa_handler = int_handle;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);

	while (1) {
		printf("I'm sleepy..\n");
		sleep(1);
		if (num >= 2) {
			//act.sa_handler = SIG_DFL;
			act.sa_handler = SIG_IGN;
			sigaction(SIGINT, &act, NULL);
		}
	}
}

void int_handle(int signum){
	printf("SIGINT : %d\n", signum);
	printf("int_handle called %d times\n", ++num);
}
