#include <linux/init.h>
#include <linux/module.h>

static int hello_drv_init(void)
{
    printk(KERN_ALERT "Hello, world\n");
    return 0;
}

static void hello_drv_exit(void)
{
    printk(KERN_ALERT "Goodbye, world\n");
}

module_init(hello_drv_init);
module_exit(hello_drv_exit);
MODULE_LICENSE("GPL");
