# Specify the modules to be built
# obj-m specifies that gpioDriver.o should be built as a loadable kernel module
obj-m += gpioDriver.o

# List the source files to be compiled into gpioDriver.o
# gpioDriver-y lists the source files for the gpioDriver module
gpioDriver-y := gpio.o gpio-file-operations.o

# Get the current working directory
SRC := $(shell pwd)

# The default target
all:
	# Invoke the kernel build system
	# -C $(KERNEL_SRC) changes to the kernel source directory
	# M=$(PWD) specifies the directory of the module source files
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)

# Install target to install the modules
modules_install:
	# Invoke the kernel build system to install the modules
	# -C $(KERNEL_SRC) changes to the kernel source directory
	# M=$(PWD) specifies the directory of the module source files
	# modules_install tells the kernel build system to install the modules
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

# Clean target to clean up build artifacts
clean:
	# Remove generated object files, backup files, core dumps, and other artifacts
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	# Remove additional kernel build system artifacts
	rm -f Module.markers Module.symvers modules.order
	# Remove temporary versioning files
	rm -rf .tmp_versions
	# Remove Module.symvers (if exists) which stores information about exported symbols