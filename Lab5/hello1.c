#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Dmytro Lutsenko");
MODULE_DESCRIPTION("Hello1 module");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_list);

void print_hello(uint count)
{
	int i;
	struct hello_item *item;

	for (i = 0; i < count; i++) {
		item = kmalloc(sizeof(*item), GFP_KERNEL);
		if (!item) {
			pr_err("Failed to allocate memory\n");
			return;
		}
		item->time = ktime_get();
		list_add_tail(&item->list, &hello_list);
		pr_info("Hello, world! %u\n", i + 1);
	}
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct hello_item *item, *tmp;

	pr_info("Exiting hello1 module and printing stored times:\n");

	list_for_each_entry_safe(item, tmp, &hello_list, list) {
		pr_info("Time: %lld ns\n", ktime_to_ns(item->time));
		list_del(&item->list);
		kfree(item);
	}
}

module_exit(hello1_exit);
