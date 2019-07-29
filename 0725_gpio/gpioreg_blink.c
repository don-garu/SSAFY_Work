#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(){
	int mem_fd, i;
	volatile unsigned *GPIO_BASE;
	volatile unsigned *GPIO_GPFSEL1;
	volatile unsigned *GPIO_GPSET0;
	volatile unsigned *GPIO_GPCLR0;

//	mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	mem_fd = open("/dev/gpiomem", O_RDWR | O_SYNC);
	if (mem_fd < 0){
		printf("Cannot open /dev/mem\n");
		exit(-1);
	}

	GPIO_BASE = (char *)mmap(0, 0x60, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, 0x3f200000);
	GPIO_GPFSEL1 = (volatile unsigned *)(GPIO_BASE + 0x04/4);
	GPIO_GPSET0 = (volatile unsigned *)(GPIO_BASE + 0x1c/4);
	GPIO_GPCLR0 = (volatile unsigned *)(GPIO_BASE + 0x28/4);

	*GPIO_GPFSEL1 &= 0xff1fffff;
	usleep(2000);
	*GPIO_GPFSEL1 |= (0x1 << 21);
	usleep(2000);

	for (i = 0; i<5; i++){
		*GPIO_GPSET0 |= (1<<17);
		sleep(1);

		*GPIO_GPCLR0 |= (1<<17);
		sleep(1);
	}
	close(mem_fd);
	munmap(GPIO_BASE, 0x60);

	return 0;
}
