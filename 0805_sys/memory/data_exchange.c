#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){
	int fd, status;
	pid_t pid;
	caddr_t addr;
	struct stat sbuf;

	if (argc != 2){
		fprintf(stderr, "Usage : %s filename\n", argv[0]);
		exit(1);
	}

	if (stat(argv[1], &sbuf) == -1){
		perror("stat");
		exit(1);
	}

	if ((fd = open(argv[1], O_RDWR)) == -1){
		perror("open");
		exit(1);
	}

	addr = mmap(NULL, sbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
	if (addr == MAP_FAILED){
		perror("mmap");
		exit(1);
	}
	close(fd);

	switch (pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("1. Child Process : addr = %s\n", addr);
			sleep(1);
			addr[0] = 'x';
			printf("2. Child Process : addr = %s\n", addr);
			sleep(2);
			printf("3. Child Process : addr = %s\n", addr);
			exit(1);
			break;
		default:
			printf("1. Parent Process : addr = %s\n", addr);
			sleep(2);
			printf("2. Parent Process : addr = %s\n", addr);
			addr[1] = 'y';
			printf("3. Parent Process : addr = %s\n", addr);
			break;
	}
	wait(&status);

	return 0;
}
