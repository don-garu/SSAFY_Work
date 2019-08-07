#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int fd;
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

	printf("%s", addr);
	
	if (munmap(addr, sbuf.st_size) == -1){
		perror("munmap");
		exit(1);
	}

//	printf("%s", addr); // Use unmmaped memory -> Segmentation Fault

	return 0;
}
