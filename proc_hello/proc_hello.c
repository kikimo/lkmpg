#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define HELLO_PROC_ENTRY "hello"

struct proc_dir_entry *proc_hello;
struct file_operations proc_hello_fops;

// 1. proc file entry
// 2. proc_read_entry

static int __init init_hello_proc(void)
{
    struct file_operations *fops = &proc_hello_fops;

    printk(KERN_INFO "proc hello init.\n");

    fops->read = NULL;
    fops->llseek = NULL;
    if ((proc_hello = proc_create(HELLO_PROC_ENTRY, 0644, NULL, fops)) == NULL) {
        // TODO return error
        // proc_remove(proc_hello);
        return -ENOMEM;
    }

    return 0;
}

static void __exit cleanup_hello_proc(void)
{
    printk(KERN_INFO "proc hello exit.\n");

    if (proc_hello != NULL) {
        proc_remove(proc_hello);
    }

    return;
}

module_init(init_hello_proc);
module_exit(cleanup_hello_proc);
