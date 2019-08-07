#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(){
	int fd, i, *pointer;
	
	if ((fd = open("mmap.dat", O_RDWR | O_CREAT, 0666)) == -1){
		perror("open");
		exit(1);
	}
	ftruncate(fd, 4096);

	pointer = (int*)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if ((unsigned)pointer == (unsigned)-1){
		perror("mmap");
		exit(1);
	}

	for (i = 0; i<100; i++){
		pointer[i] = i*i;
	}

	pointer[i+1] = -1;
	getchar();
	munmap(pointer, 4096);
	close(fd);
	
	return 0;
}
