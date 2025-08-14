#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>

#define MIN(a, b) (a < b ? a : b)

static char kernel_buf[1024];
static struct class *mychardev_class;
static dev_t dev_num;
static int major, minor = 0;
struct cdev c_device;

static int chrdev_open(struct inode *inode, struct file *file)
{
    printk(KERN_ALERT "Open hello char drive\n");
    return 0;
}

static int chrdev_release(struct inode *inode, struct file *file)
{
    printk(KERN_ALERT "Close hello char drive\n");
    return 0;
}

static ssize_t chrdev_read(struct file *file, char *buf, size_t len, loff_t *offset)
{

    size_t to_copy = MIN(len, sizeof(kernel_buf));
    if (copy_to_user(buf, kernel_buf, to_copy))
        return -EFAULT;
    printk(KERN_ALERT "Read message from kernel \n");

    return to_copy;
}

ssize_t chrdev_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    printk(KERN_ALERT "Write message to kernel\n");
    size_t from_copy = MIN(len, sizeof(kernel_buf));

    if (copy_from_user(kernel_buf, buf, from_copy))
        return -EFAULT;
    return from_copy;
}

// file operations
static const struct file_operations chrdev_fops = {
    .owner = THIS_MODULE,
    .open = chrdev_open,
    .read = chrdev_read,
    .release = chrdev_release,
    .write = chrdev_write,
};

static int __init chrdrv_init(void)
{

    // 1. 分配設備號
    int ret = alloc_chrdev_region(&dev_num, 0, 1, "mychardev");
    if (ret < 0)
        return ret;
    printk(KERN_ALERT "Major deice num = %d\n", MAJOR(dev_num));

    // 2. 初始化並添加 cdev
    cdev_init(&c_device, &chrdev_fops);
    cdev_add(&c_device, dev_num, 1);

    // 3. 建立 /dev/mychardev
    mychardev_class = class_create(THIS_MODULE, "mychardev_class");
    device_create(mychardev_class, NULL, dev_num, NULL, "mychardev");

    return 0;
}

static void __exit chrdrv_exit(void)
{
    printk(KERN_ALERT "Driver Exit!\n");
    device_destroy(mychardev_class, dev_num);
    class_destroy(mychardev_class);
    cdev_del(&c_device);
    unregister_chrdev_region(dev_num, 1);
}

module_init(chrdrv_init);
module_exit(chrdrv_exit);

MODULE_LICENSE("GPL");