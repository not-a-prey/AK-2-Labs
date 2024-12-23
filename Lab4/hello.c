#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/atomic.h>

MODULE_AUTHOR("Lutsenko Dmytro");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0644);
MODULE_PARM_DESC(count, "Number of times to print 'Hello, world!'");

struct hello_item {
	struct list_head list;
	ktime_t time;
};

static LIST_HEAD(hello_list);

static int __init hello_init(void)
{
	int i;
	struct hello_item *item;

	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("Warning: count is 0 or between 5 and 10\n");
	} else if (count > 10) {
		pr_err("Error: count is greater than 10\n");
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		item = kmalloc(sizeof(*item), GFP_KERNEL);
		if (!item) {
			pr_err("Failed to allocate memory\n");
			return -ENOMEM;
		}
		item->time = ktime_get();
		list_add_tail(&item->list, &hello_list);
		pr_info("Hello, world! %u\n", i + 1);
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct hello_item *item, *tmp;

	pr_info("Exiting module and printing stored times:\n");

	list_for_each_entry_safe(item, tmp, &hello_list, list) {
		pr_info("Time: %lld ns\n", ktime_to_ns(item->time));
		list_del(&item->list);
		kfree(item);
	}
}

module_init(hello_init);
module_exit(hello_exit);
