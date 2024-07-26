#include "gpio-file-operations.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelaziz Maher");
MODULE_DESCRIPTION("A gpio driver");

#define DRIVER_NAME "led-home"
#define DRIVER_CLASS "gpio-class"

struct mydata
{
    /* uint32 holds the driver device number(major + minor) */
    dev_t device_number;
    /* character device structure */
    struct cdev cdev_obj;
    /* file operations of the driver */
    struct file_operations fops;
    /* pointer to class (higher-level view of a device that abstracts out low-level implementation details) structure */
    struct class *gpio_class;
    /* pointer to device (contains the informations that the device model core needs to model the system) structure */
    struct device *gpio_device;
} gpioData_st = {
    .fops = {
        .owner = THIS_MODULE,
        .open = driver_open,
        .release = driver_release,
        .read = driver_read,
        .write = driver_write,
    }
};

static int __init driver_INIT(void)
{
    int ret;

    /* 1. Dynamically allocate device number region */
    ret = alloc_chrdev_region(&gpioData_st.device_number, 0, 1, DRIVER_NAME);
    if (ret < 0)
    {
        pr_err("Alloc chrdev numbers failed\n");
        goto alloc_fail;
    }

    /* 2. Initialize cdev structure with its file operations */
    cdev_init(&gpioData_st.cdev_obj, &gpioData_st.fops);

    /* 3. Register cdev structure with VFS */
    gpioData_st.cdev_obj.owner = THIS_MODULE;
    ret = cdev_add(&gpioData_st.cdev_obj, gpioData_st.device_number, 1);
    if (ret < 0)
    {
        pr_err("Cdev addition failed\n");
        goto cdev_fail;
    }

    /* 4. Create device class under sys/class/<class name> */
    gpioData_st.gpio_class = class_create(THIS_MODULE, DRIVER_CLASS);
    if (IS_ERR(gpioData_st.gpio_class)) /*ERR_PTR() on error*/
    {
        pr_err("Class creation failed\n");
        /* Convert pointer to error code(int)*/
        ret = PTR_ERR(gpioData_st.gpio_class);
        goto class_fail;
    }

    /* 5. Create device under sys/class/<class name>/<device name> and populate it with device info */
    gpioData_st.gpio_device = device_create(gpioData_st.gpio_class, NULL, gpioData_st.device_number, NULL, DRIVER_NAME);
    if (IS_ERR(gpioData_st.gpio_device)) /*ERR_PTR() on error*/
    {
        pr_err("Device creation failed\n");
        /* Convert pointer to error code(int)*/
        ret = PTR_ERR(gpioData_st.gpio_device);
        goto device_fail;
    }

    /* 6. Requesting the GPIO*/
    if (gpio_request(21, "GPIO_21") < 0)
    {
        pr_err("Cannot allocat GPIO pin\n");
        goto device_fail;
    }

    /* 7. Configure the GPIO as output*/
    if (gpio_direction_output(21, 0))
    {
        pr_err("Cannot SET GPIO pin\n");
        goto gpio21_fail;
    }

    return 0;

gpio21_fail:
    gpio_free(21);
device_fail:
    class_destroy(gpioData_st.gpio_class);
class_fail:
    cdev_del(&gpioData_st.gpio_device);
cdev_fail:
    unregister_chrdev_region(gpioData_st.device_number, 1);
alloc_fail:
    printk("Module insertion failed\n");

    return ret;
}

static void __exit driver_EXIT(void)
{
    /* 1. Reset pin */
    gpio_set_value(21, 0);

    /* 2. Free gpio pin */
    gpio_free(21);

    /* 3. Remove device */
    device_destroy(gpioData_st.gpio_class, gpioData_st.device_number);

    /* 4. Destroy class */
    class_destroy(gpioData_st.gpio_class);

    /* 5. Delete cdev */
    cdev_del(&gpioData_st.cdev_obj);

    /* 6. unregister a range of device numbers */
    unregister_chrdev_region(gpioData_st.device_number, 1);
}

module_init(driver_INIT);
module_exit(driver_EXIT);