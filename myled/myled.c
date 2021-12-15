#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Kazuki Miyamoto  and  Ryuichi Ueda");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static ssize_t led_write(struct file* flip, const char* buf, size_t count, loff_t* pos)
{
	char c;

	if(copy_from_user(&c,buf,sizeof(char)))
	{	return -EFAULT;
	}
//	printk(KERN_INFO "receive %c\n",c);

	if(c == '0')
	{
		gpio_base[10] =1 << 25;
		gpio_base[10] =1 << 8;
	}
	 if(c == '1')
	{
		gpio_base[7] = 1 << 25;//GPIO25
		gpio_base[10] = 1 << 8;
	}
	 if(c == '2')
	{
		gpio_base[10] = 1 << 25;
		gpio_base[7] = 1 << 8;//GPIO21
	}
	 if(c == '3')
	 {
		 int i;
		 for(i=0;i<4;i++)
		 {
			 {
			 gpio_base[7] = 1 << 25;
			 gpio_base[10] = 1 << 8;
			 }ssleep(1);
			
			 {
			 gpio_base[10] = 1 << 25;
		 	 gpio_base[7] = 1 << 8;
			 }ssleep(1);
		 }

		 gpio_base[10] = 1 << 25;
		 gpio_base[10] = 1 <<8;
	 }
	if(c == '4'){
		int j;

		for(j=0;j<15;j++){
		{
		 gpio_base[7] = 1 << 25;
		 gpio_base[10] = 1 << 8;
		 }msleep(100);

		{
		 gpio_base[10] = 1 << 25;
		 gpio_base[7] = 1 << 8;
		 }msleep(100);
		}

		gpio_base[10] = 1 << 25;
		gpio_base[10] = 1 << 8;
	}

printk("∧___∧\n(´･ω･)みなさん、お茶が入りましたよ・・・・.\n( つ旦O\nと＿)＿)\n ");

return 1;
}

static ssize_t sushi_read(struct file* flip, char* buf, size_t count, loff_t* pos)
{
	int size = 0;
	char sushi[] = {'u','n','c','h','i'};
	if(copy_to_user(buf+size,(const char *)sushi, sizeof(sushi))){
		printk( KERN_ERR "sushi : copy_to_user failed\n");
		return -EFAULT;
	}
	size += sizeof(sushi);
	return size;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read
};

static int __init init_mod(void) //カーネルモジュールの初期化
{
	int retval;
	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0) {
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}

	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));
	
	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d\n",MAJOR(dev),MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE, "myled");
	if(IS_ERR(cls)) {
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}

	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));

	gpio_base = ioremap_nocache(0x3f200000,0xA0);

	const u32 led = 25;
	const u32 index = led/10;
	const u32 shift = (led%10)*3;
	const u32 mask = ~(0x7 << shift);
	gpio_base[index] =  (gpio_base[index] & mask) | (0x1 << shift);

//	const u32 led2 = 8;
//	const u32 index2 = led2/10;
//	const u32 shift2 = (led2%10)*3;
//	const u32 mask2 = ~(0x7 << shift2);
//	gpio_base[index2] =  (gpio_base[index2] & mask2) | (0x1 << shift2);
	
	return 0;
}

static void __exit cleanup_mod(void) //後始末
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO"%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod);     //マクロで関数を登録
module_exit(cleanup_mod); //同上
