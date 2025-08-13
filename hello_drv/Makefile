obj-m := hello_drv.o

KDIR := /home/yochen0125/100ask_imx6ull-sdk/Linux-4.9.88
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean