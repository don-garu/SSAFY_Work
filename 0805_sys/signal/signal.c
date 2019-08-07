#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sig_usr(int);

int main(){
	printf("My PID : %d\n", getpid());
	if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
		perror("Can't catch SIGUSR1");
		return -1;
	}
	if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
		perror("Can't catch SIGUSR2");
		return -1;
	}
	while (1)
		pause();

	return 0;
}

static void sig_usr(int signo){
	switch (signo){
		case SIGUSR1:
			printf("Received SIGUSR1\n");
			break;
		case SIGUSR2:
			printf("Received SIGUSR2\n");
			break;
		default:
			fprintf(stderr, "Received signal %d\n", signo);
	}
	return;
}
