#include <linux/module.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <stdlib.h>


MODULE_LICENSE("GPL");
irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs *regs) {
    static unsigned char scancode, status;
    status   = inb(0x64);
    scancode = inb(0x60);
    printk (KERN_INFO "! You pressed Esc scancode: %d...\n", scancode);
    printk (KERN_INFO "! status: %d...\n", status);
 /* #include <sys/ipc.h>
 #include <sys/shm.h>
 #int shmget(key_t key, size_t size, int shmflg)   
   switch (scancode) shmget() shmat()
    {
    case 0x01:  printk (KERN_INFO "! You pressed Esc ...\n");
          break;
    case 0x3B:  printk (KERN_INFO "! You pressed F1 ...\n");
          break;
    case 0x3C:  printk (KERN_INFO "! You pressed F2 ...\n");
          break;
    default: break;
    }*/
    return IRQ_HANDLED;
}
static int __init irq_ex_init(void) {
    printk (KERN_INFO "DEVICE OPEN...\n");
    free_irq(125,NULL);
    return request_irq (125,(irq_handler_t)irq_handler,IRQF_SHARED,"test_usb_irq_handler",(void*)(irq_handler));
}
static void __exit irq_ex_exit(void) {
    printk (KERN_INFO "!DEVICE CLOSE...\n");
}
module_init(irq_ex_init);
module_exit(irq_ex_exit);
