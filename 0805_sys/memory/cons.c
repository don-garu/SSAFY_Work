#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
	int fd, i = 0, *pointer;
	char *file = NULL, *linebuf;

	if ((fd = open("mmap.dat", O_RDWR, 0666)) < 0){
		perror("Open");
		exit(1);
	}

	if ((pointer = (int *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == NULL){
		perror("mmap");
		exit(1);
	}

	while (1){
		if (pointer[i] == -1)
			break;
		printf("> %d\n", pointer[i++]);
	}

	close(fd);
	munmap(pointer, 4096);
	
	return 0;
}
