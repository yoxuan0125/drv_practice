#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

static const struct file_operations chrdev_fops = {
    .owner = THIS_MODULE,
    .open = chrdev_open,
    .read = chrdev_read,
    .release = chrdev_release,
    .write = chrdev_write,
};

int chrdev_open(struct inode *inode, struct file *file)
{
}