obj-m = toggle_smep.o
M=$(shell pwd)

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(M) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(M) clean
