#include "gpio-file-operations.h"

static int driver_open(struct inode *inode, struct file *file)
{
    printk("Module open function called\n");
    return 0;
}

static int driver_close(struct inode *inode, struct file *file)
{
    printk("Module close function called\n");
    return 0;
}

static int driver_release(struct inode *device_file, struct file *instance)
{
    printk("Module release function called\n");
    return 0;
}

ssize_t driver_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
    printk("Driver read is called but this pin is output\n");
    return -ENOSYS;
}

ssize_t driver_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
    /* 1. Value to hold the input data */
    char value;

    /* 2. Return error if no data to write */
    if (!count)
        return -ENOMEM;

    /* 4. Copy data from user ( returns --> (0 on success) */
    if (copy_from_user(&value, buff, sizeof(value)))
        return -EFAULT;

    /* 5. Update the current file position */
    switch (value)
    {
    case '0':
        gpio_set_value(21, 0);
        break;
    case '1':
        gpio_set_value(21, 1);
        break;
    default:
        pr_err("Invalid input\n");
        break;
    }

    /* 5. return number of bytes wriiten */
    return count;
}