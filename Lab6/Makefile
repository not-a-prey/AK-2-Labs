ifneq ($(KERNELRELEASE),)

# kbuild
obj-m := hello.o
ccflags-y += -g   # + debugging

else

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello.ko hello.ko.unstripped
	$(CROSS_COMPILE)strip -g hello.ko   # only debugging information

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

%.s %.i: %.c 
	$(MAKE) -C $(KDIR) M=$$PWD $@

endif
