#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

/*
	- LED out : GPIO Header Pin 11, BCM#17
	- SW in : GPIO Header Pin 13, BCM#27
*/

int main(){
	int mem_fd, i;
	int set;
	volatile unsigned *GPIO_BASE;
	volatile unsigned *GPIO_GPFSEL1;
	volatile unsigned *GPIO_GPFSEL2;
	volatile unsigned *GPIO_GPSET0;
	volatile unsigned *GPIO_GPCLR0;
	volatile unsigned *GPIO_GPLEV0;

	mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (mem_fd < 0){
		printf("Can't Open /dev/mem\n");
		exit(-1);
	}

	GPIO_BASE = (unsigned int*)mmap(0, 0x60, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, 0x3F200000);
	GPIO_GPFSEL1 = (volatile unsigned int*)(GPIO_BASE + 0x04 / 4);
	GPIO_GPFSEL2 = (volatile unsigned int*)(GPIO_BASE + 0x08 / 4);
	GPIO_GPSET0 = (volatile unsigned int*)(GPIO_BASE + 0x1c / 4);
	GPIO_GPCLR0 = (volatile unsigned int*)(GPIO_BASE + 0x28 / 4);
	GPIO_GPLEV0 = (volatile unsigned int*)(GPIO_BASE + 0x34 / 4);
	
	*GPIO_GPFSEL1 &= 0xff1fffff;
	usleep(2000);

	*GPIO_GPFSEL2 &= 0xff1fffff;
	usleep(2000);

	*GPIO_GPLEV0 &= (0x0 << 27);
	usleep(2000);

	set = 0;
	while (1){
		if (*GPIO_GPLEV0 & (0x1 << 27)){
			set = !set;
			printf("GPLEV0 is TRUE\n");

			*GPIO_GPFSEL1 |= (0x1 << 21);
			usleep(2000);

			if (set)
				*GPIO_GPSET0 |= (1 << 17);
			else
				*GPIO_GPCLR0 |= (1 << 17);
			sleep(1);
		}
	}
	close(mem_fd);
	munmap((void*)GPIO_BASE, 0x60);

	return 0;
}
