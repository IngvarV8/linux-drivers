#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>


static ssize_t	read_function(struct file* fp, char* user_buffer, size_t count, loff_t* offset){
    printk("Read function called");

    char * msg = "msg from kernel to userspace\n";
    size_t len = strlen(msg);

    int result;

    if (*offset > len){
        return 0;
    }

    result = copy_to_user(user_buffer, msg, 29);
    *offset += len;
    

    
    return len;
}

static struct proc_dir_entry* my_proc_dir_entry;
struct proc_ops my_proc_ops = {
    .proc_read = read_function
};

//ssize_t	(*proc_read)(struct file *, char __user *, size_t, loff_t *);
// struct proc_dir_entry *proc_create(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct proc_ops *proc_ops);

static int __init simple_init(void) {
    printk(KERN_INFO "Starting init of driver\n");
    my_proc_dir_entry = proc_create("ingv_custom_driver", 0, NULL, &my_proc_ops);
    
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
