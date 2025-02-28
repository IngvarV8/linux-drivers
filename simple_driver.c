#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init simple_init(void) {
    printk(KERN_INFO "Hello, Linux Driver!\n");
    return 0;
}

static void __exit simple_exit(void) {
    printk(KERN_INFO "Goodbye, Linux Driver!\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Simple Linux Driver");
