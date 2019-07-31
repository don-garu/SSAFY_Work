#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void f1(), f2();

int main(){
	printf("[%d]test\n", getpid());
	f1();
	printf("[%d]test\n", getpid());
	f2();
	printf("[%d]test\n", getpid());
	exit(0);
}

static void f1(){
	pid_t pid;

	if ((pid = vfork()) < 0)
		perror("Vfork error");
}

static void f2(){
	printf("[%d]test\n", getpid());
	char buf[1000];
	int i;
	for (i = 0; i<sizeof(buf); i++)
		buf[i] = 0;
	printf("[%d]test\n", getpid());
}
