#include <linux/module.h> /* Needed by all modules */ 
#include <linux/printk.h> /* Needed for pr_info() */ 

void show(void) {
	pr_info("Hello world 1.\n");
	
	}
EXPORT_SYMBOL_GPL(show);

int init_module(void) { 
    pr_info("Function was declared.\n");
	return 0; 
} 
 
void cleanup_module(void) { 
	 
} 
 
MODULE_LICENSE("GPL");
