
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <linux/sched/signal.h>   // include may differe depending on the linux kernel version


/* This function is called when the module is loaded. */
int linear_init(void)
{
	struct task_struct *task;
	for_each_process(task)       // Linearly iterates over running processes
	{
		printk(KERN_INFO "Task %s (pid = %d) state %ld \n", task->comm, task->pid, task->state);  // Prints process information
	}

	return 0;
}

/* This function is called when the module is removed. */
void linear_exit(void) {
        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

/* Macros for registering module entry and exit points. */
module_init( linear_init );   // Entry point 
module_exit( linear_exit );   // Exit point

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linear listing Module");
MODULE_AUTHOR("SGG");
