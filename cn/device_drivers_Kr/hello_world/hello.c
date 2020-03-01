#include<linux/init.h>
#include<linux/module.h>
int hello_init(void)
{
	printk(KERN_ALERT "I am inside %s",__FUNCTION__);
	return 0;
}
void hello_exit(void)
{
	printk(KERN_ALERT "I am outside %s",__FUNCTION__);
}
module_init(hello_init);
module_exit(hello_exit);
//MODULE_LICENSE("GPL");
