#include <linux/module.h> /* Needed by all modules */ 
#include <linux/printk.h> /* Needed for pr_info() */ 
 
int init_module(void) { 
	show();
} 
 
void cleanup_module(void) { 
} 
 
MODULE_LICENSE("GPL");
