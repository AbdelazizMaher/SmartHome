#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

/**
 * @brief Called when the device file is opened.
 * 
 * This function is responsible for initializing the device or performing any
 * setup needed when the device file is accessed. It may also perform any 
 * necessary checks or initialization specific to the file or device.
 * 
 * @param inode Pointer to the inode structure representing the file on disk.
 * @param file Pointer to the file structure representing the open file in memory.
 * @return 0 on success, or a negative error code on failure.
 */
static int driver_open(struct inode *inode, struct file *file);


/**
 * @brief Called when the device file is closed.
 * 
 * This function is responsible for cleaning up or releasing any resources
 * allocated when the device file was opened. It is called when the file is
 * closed or the last reference to the device is released.
 * 
 * @param inode Pointer to the inode structure representing the file on disk.
 * @param file Pointer to the file structure representing the open file in memory.
 * @return 0 on success, or a negative error code on failure.
 */
static int driver_close(struct inode *inode, struct file *file);

/**
 * @brief Called when the device file is released.
 * 
 * This function is similar to `driver_close` but is specifically used for
 * releasing resources associated with the file descriptor when it is closed.
 * 
 * @param device_file Pointer to the inode structure representing the file on disk.
 * @param instance Pointer to the file structure representing the open file in memory.
 * @return 0 on success, or a negative error code on failure.
 */
static int driver_release(struct inode *device_file, struct file *instance);


/**
 * @brief Handles read operations from the device.
 * 
 * This function is responsible for copying data from the device to the user-space
 * buffer. It reads data based on the file position and count, and updates the
 * file position pointer accordingly.
 * 
 * @param filp Pointer to the file structure representing the open file in memory.
 * @param buff Pointer to the user-space buffer where data will be copied.
 * @param count Number of bytes to read.
 * @param f_pos Pointer to the file position, which will be updated.
 * @return Number of bytes read, or a negative error code on failure.
 */
ssize_t driver_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos);

/**
 * @brief Handles write operations to the device.
 * 
 * This function is responsible for copying data from the user-space buffer to the
 * device. It writes data based on the file position and count, and updates the
 * file position pointer accordingly.
 * 
 * @param filp Pointer to the file structure representing the open file in memory.
 * @param buff Pointer to the user-space buffer containing data to be written.
 * @param count Number of bytes to write.
 * @param f_pos Pointer to the file position, which will be updated.
 * @return Number of bytes written, or a negative error code on failure.
 */
ssize_t driver_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos);