CC=arm-linux-gnueabihf-gcc

default:
	$(CC) -o gpioblink gpioreg_blink.c
	$(CC) -o gpioswitch gpio_switch_input.c
	scp gpioblink gpioswitch pi@70.12.230.173:~/workspace/gpio/
clean:
	rm gpioblink gpioswitch gpiotest

gpioblink: gpioreg_blink.c
gpioswitch: gpio_switch_input.c
