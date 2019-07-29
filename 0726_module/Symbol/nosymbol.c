#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int module_begin(void){
	printk(KERN_INFO "Hi, No Symbol!\n");
	return 0;
}

static void module_end(void){
	printk("Good bye, No Symbol.\n");
}

MODULE_LICENSE("GPL");
EXPORT_NO_SYMBOLS;
module_init(module_begin);
module_exit(module_end);
