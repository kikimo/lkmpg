#include <linux/kernel.h>  // for printk()
#include <linux/module.h>  // required by kernel module

// init_module() will conflict with module_init() so we use
// init_hello() instead.
static int __init init_hello(void)
{
    printk(KERN_INFO "kern hello world\n");
    return 0;
}

// same as init_hello()
static void __exit cleanup_hello(void)
{
    printk(KERN_INFO "kern hello exit!\n");
    return;
}

module_init(init_hello);
// kmodule will failed to unload withoud module_exit function.
module_exit(cleanup_hello);

