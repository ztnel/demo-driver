
#include <linux/init.h>
#include <linux/module.h>

static int __init test_init(void) {
  printk(KERN_INFO "Hello World.\n");
  return 0;
}

static void __exit test_exit(void) {
  printk(KERN_ALERT "Goodbye World.\n");
  return;
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");