# Include the base recipe for the minimal core image.
include recipes-core/images/core-image-minimal.bb


# This enables the Dropbear SSH server for secure shell access.
IMAGE_FEATURES += "ssh-server-dropbear "


# Install kernel modules to ensure kernel modules are included in the image
IMAGE_INSTALL += "kernel-modules "  

# Install tools for debugging and building.
IMAGE_INSTALL += "strace bash make cmake " 

# Network(wifi) management and firmware. 
IMAGE_INSTALL += "dhcpcd iptables "

# applications and services.  
IMAGE_INSTALL += "device-controller frontend nginx configstartup-sv " 
IMAGE_INSTALL += "gpio-mod " 
IMAGE_INSTALL += "nodejs fota-server " 


# Automatically load kernel modules on boot.
KERNEL_MODULE_AUTOLOAD += "gpioDriver"


# This function appends configuration settings to `dhcpcd.conf`.
my_fixed_ip() {
    echo "
interface eth0
static ip_address=10.42.0.2/24
static routers=10.42.0.1
static domain_name_servers=10.42.0.1 8.8.8.8
" >> ${IMAGE_ROOTFS}/etc/dhcpcd.conf
}

# This ensures that the static IP configuration is applied to the image after installation.
ROOTFS_POSTINSTALL_COMMAND += "my_fixed_ip; "

