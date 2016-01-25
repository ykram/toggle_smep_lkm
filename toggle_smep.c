#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

void toggle_smep(int smep_on)
{
	unsigned long cr4 = 0;

	__asm__("movq %%cr4, %0;"
		: "=a" (cr4) : : );

	if (smep_on == 0)
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

int init_mod(void)
{
	pr_debug("Turning SMEP off...\n");
	toggle_smep(0);

	return 0;
}

void cleanup_mod(void)
{
	pr_debug("Turning SMEP back on...\n");
	toggle_smep(1);
}

module_init(init_mod);
module_exit(cleanup_mod);
