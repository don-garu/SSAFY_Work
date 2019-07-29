obj-m := module_hello.o
KDIR := ~/Work/Rpi/linux
PWD := $(shell pwd)
ARM := ARCH=arm
CROSS_COMPILE := CROSS_COMPILE=arm-linux-gnueabihf-
MAKE_ARCH := $(MAKE) $(ARM) $(CROSS_COMPILE)

default:
	$(MAKE_ARCH) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE_ARCH) -C $(KDIR) M=$(PWD) clean

