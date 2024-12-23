#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Dmytro Lutsenko");
MODULE_DESCRIPTION("Hello2 module");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0644);
MODULE_PARM_DESC(count, "Number of times to print 'Hello, world!'");

static int __init hello2_init(void)
{
	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("Warning: count is 0 or between 5 and 10\n");
	} else if (count > 10) {
		pr_err("Error: count is greater than 10\n");
		return -EINVAL;
	}

	pr_info("Calling print_hello() from hello2 module...\n");
	print_hello(count);

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Exiting hello2 module\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
