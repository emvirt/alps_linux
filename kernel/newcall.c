#include <linux/kernel.h>
#include <linux/io.h>
#include <asm/hardware/gic.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

static DEFINE_SPINLOCK(crash_lock);

asmlinkage int sys_newcall(void){
//        int cpu=1;
//        int irq=8;

//        for(cpu=1;cpu<4;cpu++)
//                writel_relaxed( 1 << (16 + cpu) | irq, 0xf2a01000 + GIC_DIST_SOFTINT);

//   	msleep(1000);

//      printk("Hello, Kernel\n");
        asm volatile("mov r0, #8\n;");         //hjpark T_SMC_SWITCH_BOOT
        asm volatile(".word 0xE1600070\n");
/*hjpark
        asm volatile("mov r0, #0x7\n");
        asm volatile(".word 0xE1600070\n");
*/
        return 0;
}


/* 
 * cylee: generate a kernel crash by access for address zero
 */
asmlinkage long sys_go_crash(void)
{
//unsigned long crash_lock = 0;
	spin_lock(&crash_lock);

	asm volatile(".word 0x0\n");
	panic("force-panic");

	spin_unlock(&crash_lock);
//	asm volatile("mov r0, #0");
//	asm volatile("ldr r0, [r0]");
//	asm volatile("mcr p15, 0, r0, c12, c0, 0");

	return 0;
}
