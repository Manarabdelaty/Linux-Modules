#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>    // Include may differe depending on the linux kernle version

// Recursively iterates over the children of the task pointer
void dfs(struct task_struct *task)
{
  struct task_struct *task_next;  // pointer to head node of the list to be traversed 
  struct list_head *list;         // pointer to the head of the list

  list_for_each(list, &task->children) {
    task_next = list_entry(list, struct task_struct, sibling);    //task_next points to the next child in the list

    printk(KERN_INFO "Task %s (pid = %d) state %ld \n",task_next->comm, task_next->pid, task_next->state); // prints task pid , state , comm

    dfs(task_next);    // recursive call on the child
  }  
}

// Called when the module is loaded
int dfs_init(void)
{
  dfs(&init_task);    // Recursive call on the DFS function on the children of init_task
  return 0;
}
//Called when the module is removed
void dfs_exit(void)
{
  printk(KERN_INFO "Module removed.\n");
}

// Macros to register the entry and exit points of the module
module_init(dfs_init);  // Entry point
module_exit(dfs_exit); // Exit Point

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DFS listing Module");
MODULE_AUTHOR("SGG");
