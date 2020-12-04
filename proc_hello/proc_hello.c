#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define HELLO_PROC_ENTRY "hello"

// 1. proc file entry
// 2. proc_read_entry

char data[4096];
char pos;

ssize_t proc_hello_read(struct file * file, char __user *buf, size_t sz, loff_t *off)
{
    char *greeting = "hello world\n";
    ssize_t len = strlen(greeting);
    
    if (*off > 0) {
        return 0;
    }

    if (copy_to_user(buf, greeting, len)) {
        return -EFAULT;
    }

    *off = len;

    return len;
}

struct file_operations proc_hello_fops = {
    .read = proc_hello_read,
};
struct proc_dir_entry *proc_hello_ent;

static int __init init_hello_proc(void)
{
    printk(KERN_INFO "proc hello init.\n");

    pos = 0;
    if ((proc_hello_ent = proc_create(HELLO_PROC_ENTRY, 0644, NULL, &proc_hello_fops)) == NULL) {
        return -ENOMEM;
    }

    return 0;
}

static void __exit cleanup_hello_proc(void)
{
    printk(KERN_INFO "proc hello exit.\n");

    if (proc_hello_ent != NULL) {
        proc_remove(proc_hello_ent);
    }

    return;
}

module_init(init_hello_proc);
module_exit(cleanup_hello_proc);
