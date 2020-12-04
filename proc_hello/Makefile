obj-m += proc_hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install: all
	insmod proc_hello.ko

uninstall:
	rmmod proc_hello

.PHONY: install

