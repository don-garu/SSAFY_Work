obj-m := symbol1.o symbol2.o
KDIR := ~/Work/Rpi/linux
PWD := $(shell pwd)
ARM := ARCH=arm
CROSS_COMPILE := CROSS_COMPILE=arm-linux-gnueabihf-
MAKE_ARCH := $(MAKE) $(ARM) $(CROSS_COMPILE)

default:
	$(MAKE_ARCH) -C $(KDIR) M=$(PWD) modules

copy:
	scp symbol1.ko symbol2.ko pi@70.12.230.173:~/workspace/module

clean:
	$(MAKE_ARCH) -C $(KDIR) M=$(PWD) clean

