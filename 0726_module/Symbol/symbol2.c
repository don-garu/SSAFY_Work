#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

extern void symbol_test(void);

static int module_begin(void)
{
	printk("Hi, Symbol2!\n");
	symbol_test();
	return 0;
}

static void module_end(void){
	printk("Good bye, Symbol2.\n");
}

MODULE_LICENSE("GPL");
module_init(module_begin);
module_exit(module_end);
