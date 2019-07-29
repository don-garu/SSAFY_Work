#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

char *test;

void symbol_test(void)
{
	printk("%s\n", test);
}

static int module_begin(void)
{
	printk("Hi, Symbol1!\n");
	test = "This is a test.\n";
	return 0;
}

static void module_end(void)
{
	printk("Good bye, Symbol1.\n");
}

EXPORT_SYMBOL(symbol_test);

MODULE_LICENSE("GPL");
module_init(module_begin);
module_exit(module_end);
