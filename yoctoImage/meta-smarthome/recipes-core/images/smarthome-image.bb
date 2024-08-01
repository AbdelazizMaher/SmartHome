# Include the base recipe for the minimal core image.
include recipes-core/images/core-image-minimal.bb


# This enables the Dropbear SSH server for secure shell access.
IMAGE_FEATURES += "ssh-server-dropbear "


# Install kernel modules to ensure kernel modules are included in the image
IMAGE_INSTALL += "kernel-modules "  

# Install tools for debugging and building.
IMAGE_INSTALL += "strace bash make cmake " 

# Network(wifi) management and firmware. 
IMAGE_INSTALL += "dhcpcd linux-firmware-bcm43430 iptables wpa-supplicant "

# applications and services.  
IMAGE_INSTALL += "device-controller frontend nginx configstartup-sv " 



# The firmware `linux-firmware-bcm43455` is required for additional hardware support.
CORE_IMAGE_EXTRA_INSTALL += "linux-firmware-bcm43455 "

# Automatically load kernel modules on boot.
KERNEL_MODULE_AUTOLOAD += "gpio-mod "


# This function appends configuration settings to `dhcpcd.conf`.
my_fixed_ip() {
    echo "
interface wlan0
static ip_address=192.168.1.120/24
static router=192.168.1.1
static domain_name_servers=192.168.1.1 8.8.8.8
" >> ${IMAGE_ROOTFS}/etc/dhcpcd.conf
}

# This ensures that the static IP configuration is applied to the image after installation.
ROOTFS_POSTINSTALL_COMMAND += "my_fixed_ip; "

