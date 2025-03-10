#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

#define LIMIT 30

static char driver_buffer[LIMIT];

static ssize_t read_function(struct file* fp, char* user_buffer, size_t count, loff_t* offset){
    printk("Read function called");

    //char * msg = "msg from kernel to userspace\n";
    size_t len = strlen(driver_buffer);

    int result;

    if (*offset > len){
        return 0;
    }

    result = copy_to_user(user_buffer, driver_buffer, len);
    *offset += len;

    return len;
}

//ssize_t	(*proc_write)(struct file *, const char __user *, size_t, loff_t *);
static ssize_t write_function(struct file* fp, const char * user_buffer, size_t count, loff_t * data){
    printk("Write function called");
    
    printk("The message from user is %s\n", user_buffer);

    if ( copy_from_user(driver_buffer, user_buffer, count) == 0){
        printk("Successfully written from userspace\n");
        printk("Value written: %s\n", driver_buffer);
        return count;
    }

    return 0;
}

static struct proc_dir_entry* my_proc_dir_entry;

struct proc_ops my_proc_ops = {
    .proc_read = read_function,
    .proc_write = write_function
};

static int __init simple_init(void) {
    printk(KERN_INFO "Starting init of driver\n");
    my_proc_dir_entry = proc_create("ingvdr", 0666, NULL, &my_proc_ops);
    
    if (my_proc_dir_entry == NULL){
        printk("Error init module, my_proc_dir_entry in NULL");
        return -1;
    }

    printk(KERN_INFO "Finished init of driver\n");
    return 0;
}

static void __exit simple_exit(void) {
    printk(KERN_INFO "Started removing a driver\n");
    proc_remove(my_proc_dir_entry);
    printk(KERN_INFO "Finished removing a driver\n");
}


module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ingvar");
MODULE_DESCRIPTION("A Simple Linux Driver");
