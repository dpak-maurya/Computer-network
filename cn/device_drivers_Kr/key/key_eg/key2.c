#include <linux/kernel.h>
#include <linux/module.h>
#include<linux/version.h>
#include<linux/string.h>
#include<linux/uaccess.h>
#include<linux/slab.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");
#define KBD_DATA_REG        0x60    /* I/O port for keyboard data */
#define KBD_CONTROL_REG        0x64 
#define KBD_SCANCODE_MASK   0x7f
#define KBD_STATUS_MASK     0x80
#define DELAY do { mdelay(1); if (++delay > 10) break; } while(0)

static ssize_t readtime(struct file *,char *,size_t ,loff_t *);
static ssize_t writetime(struct file *,const char *,size_t ,loff_t *);
static int open_dev(struct inode *,struct file *);
static int closedev(struct inode *,struct file *);
int major;

static struct file_operations fops={
    .open=open_dev,
    .release=closedev,
    .read=readtime,
    //.write=writetime, 
};
int atoi(const char * str)
{
    int res = 0,i=0; // Initialize result
  
    // Iterate through all characters of input string and
    // update result
    for (i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';
  
    // return result.
    return res;
}
static ssize_t readtime(struct file *filep,char *buff,size_t len,loff_t *f_ops)
{
   char *b=kmalloc(40*sizeof(char),GFP_KERNEL);
   //struct timeval t1;
   struct timespec t1;
   //do_gettimeofday(&t1);
   getnstimeofday(&t1);
   sprintf(b,"%ld",t1.tv_sec);
   copy_to_user(buff,b,strlen(b));
   printk("Reading\n");  
   return len;
   	
}
ssize_t writetime(struct file *filp,const char *buff,size_t len, loff_t *off)
{
	char *b=kmalloc(30*sizeof(char),GFP_KERNEL);
   	copy_from_user(b,buff,len);//copy from filep or device
   	unsigned char val=0x00;
   	long int i=atoi(b);
   	while(i!=0)
   	{
   		int p=i%10;
   		if(p==1)
   		{val|=0x01;}
   		if(p==2)
   		{val|=0x02;}
   		if(p==3)
   		{val|=0x04;}
	}
   	long delay = 0;
	//wait till the input buffer is empty
	while (inb(KBD_CONTROL_REG) & 0x02)
		DELAY;
	outb(0xED, KBD_DATA_REG);
	DELAY;
	while (inb(KBD_CONTROL_REG) & 0x02)
		DELAY;
	outb(val, KBD_DATA_REG);
	DELAY;
	return i;
}

/*ssize_t writetime(struct file *filp,const char *buff,size_t len, loff_t *off)
{
  char *b=kmalloc(30*sizeof(char),GFP_KERNEL);
  copy_from_user(b,buff,len);
  long int i=atoi(b);
  //struct timespec ab;
  struct timespec64 ab;
  ab.tv_sec=i;
  ab.tv_nsec=0;
 // printk("%s",buff);
 //do_settimeofday(&ab);
  do_settimeofday64(&ab);
  return len;
}*/


static int open_dev(struct inode *a,struct file *filep)
{
  printk("device has been opened..\n");
  return 0;
}

static int closedev(struct inode *a,struct file *filep)
{
  printk("device closed just now..\n");
  return 0;
}

static void set_kbd_led_on(void)
{
	long delay = 0;
	//wait till the input buffer is empty
	while (inb(KBD_CONTROL_REG) & 0x02)
		DELAY;
	outb(0xED, KBD_DATA_REG);
	DELAY;
	while (inb(KBD_CONTROL_REG) & 0x02)
		DELAY;
	outb(0x07, KBD_DATA_REG);
	DELAY;
}
static void set_kbd_led_off(void)
{
	long delay = 0;
	//wait till the input buffer is empty
	while (inb(KBD_CONTROL_REG) & 0x02)
		DELAY;
	outb(0xED, KBD_DATA_REG);
	DELAY;
	while (inb(KBD_CONTROL_REG) & 0x02)
		DELAY;
	outb(0x00, KBD_DATA_REG);
	DELAY;
}

static int test_kbd_led_init(void)
{
        pr_info("%s: In init\n", __func__);
        if((major=register_chrdev(228,"led_driver",&fops))<0)
        	{pr_info("not major");return 0;}
        pr_info("led_driver is registerd with major no = %d\n ",major);
	set_kbd_led_on();
	return 0;
}

static void test_kbd_led_exit(void)
{
        pr_info("%s: In exit\n", __func__);
        unregister_chrdev(major,"led_driver");
	set_kbd_led_off();
}

module_init(test_kbd_led_init);
module_exit(test_kbd_led_exit);
