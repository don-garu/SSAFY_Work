#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
	int cnt = 1;
	int status;
	pid_t pid, pid_child;

	pid = fork();

	if (pid < 0){
		perror("Fork error");
		return -1;
	}
	else if (pid == 0){
		printf("#Child Process\n");
		while (cnt < 6){
			printf("Child[%d] : %d\n", getpid(), cnt++);
			usleep(100000);
		}
		return 99;
	}
	else {
		printf("#Parent Process\n");
		pid_child = wait(&status);

		printf("Closed Process ID = %d, ", pid_child);
		if (WIFEXITED(status)){
			printf("Normal Exit || Return : %d\n", WEXITSTATUS(status));
		}
		else {
			printf("Abnormal Exit || Return : %d\n", WEXITSTATUS(status));
		}
		while (cnt < 10){
			printf("Parent[%d] : %d\n", getpid(), cnt++);
			usleep(100000);
		}
	}
}
