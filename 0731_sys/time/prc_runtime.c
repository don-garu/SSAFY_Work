#include <sys/times.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void do_in_child(int seq, int rval);

int main(){
	srand((unsigned)times(0));

	int i = 0;
	for (i = 0; i<5; i++)
		do_in_child(i + 1, rand() % 10);

	int rval = 0;
	pid_t cpid = 0;
	while (i > 0){
		cpid = wait(&rval);
		printf("cpid : %d exit status : %x\n", cpid, rval >> 8);
		i--;
	}

	for (i = 0; i<10000000; i++)
		putchar('-');
	puts("");

	struct tms buf;
	times(&buf);

	printf("User CPU Time : %d\n", (int)buf.tms_utime);
	printf("System CPU Time : %d\n", (int)buf.tms_stime);
	printf("Children's User CPU Time : %d\n", (int)buf.tms_cutime);
	printf("Children's System CPU Time : %d\n", (int)buf.tms_cstime);

	return 0;
}

void do_in_child(int seq, int rval){
	pid_t cpid = fork();

	if (cpid == -1){
		perror("fork error");
		return;
	}

	if (cpid > 0)
		printf("fork child pid: %d\n", cpid);
	else {
		printf("pid: %d sleep %dseconds\n", getpid(), rval);

		int i = 0;
		for (i = 0; i<10000000; i++)
			putchar('.');
		puts("");

		exit(seq);
	}
}
