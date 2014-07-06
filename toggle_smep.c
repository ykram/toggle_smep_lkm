#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

void change_smep(int smep_on) {
	unsigned long cr4 = 0;

	__asm__(
		"movq %%cr4, %0;"
		: "=a" (cr4)
		:
		:
	);

	if(smep_on == 0)
		cr4 &= ~(1 << 20);
	else
		cr4 |= (1 << 20);

	__asm__(
		"movq %0, %%cr4;"
		:
		: "a"(cr4)
		:
	);
}

int init_mod(void) {
	printk(KERN_INFO "Turning SMEP off...\n");
	change_smep(0);

	return 0;
}

void cleanup_mod(void) {
	printk(KERN_INFO "Turning SMEP back on...\n");
	change_smep(1);
}

module_init(init_mod);
module_exit(cleanup_mod);
