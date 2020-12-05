#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define HELLO_PROC_ENTRY "hello"

// 1. proc file entry
// 2. proc_read_entry

char data[4096];
char pos;

ssize_t proc_hello_write(struct file *file, const char __user *buf, size_t sz, loff_t *off)
{
	if (copy_from_user(data+pos, buf, sz)) {
		return -EFAULT;
	}

	*off += sz;
	pos += sz;
	return sz;
}


ssize_t proc_hello_read(struct file * file, char __user *buf, size_t sz, loff_t *off)
{
	if (*off > 0) {
		return 0;
	}

	if (copy_to_user(buf, data, pos)) {
		return -EFAULT;
	}

	*off += pos;
	return pos;
}

struct file_operations proc_hello_fops = {
    .owner = THIS_MODULE,
    .read = proc_hello_read,
    .write = proc_hello_write,
};

struct proc_dir_entry *proc_hello_ent;

static int __init proc_hello_init(void)
{
    printk(KERN_INFO "proc hello init.\n");

    pos = 0;
    if ((proc_hello_ent = proc_create(HELLO_PROC_ENTRY, 0644, NULL, &proc_hello_fops)) == NULL) {
        return -ENOMEM;
    }

    return 0;
}

static void __exit proc_hello_exit(void)
{
    printk(KERN_INFO "proc hello exit.\n");

    if (proc_hello_ent != NULL) {
        proc_remove(proc_hello_ent);
    }

    return;
}

module_init(proc_hello_init);
module_exit(proc_hello_exit);
