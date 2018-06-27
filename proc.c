#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define FILE_NAME "info"
#define DIR_NAME "lz"
#define STRINGLEN 1024
#define AUTHOR "LIZHUANG"
#define ICENSE "GPL"
#define DRIVER_DESC "Path:/proc/$DIR_NAME/$FILE_NAME"

char global_buffer[STRINGLEN];
struct proc_dir_entry *root_dir;

MODULE_LICENSE(ICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

static int kernel_proc_show(struct seq_file *m, void *v) {
	seq_printf(m, global_buffer);
	return 0;
}

static int kernel_proc_open(struct inode *inode, struct file *file) {
	return single_open(file, kernel_proc_show, NULL);
}

int kernel_proc_write( struct file *filp, const char __user *buffer,unsigned long count, void *data){
	int len;
	if(count<=0)
	{
   return len;
  }
	if(count==STRINGLEN)
	{
		len=STRINGLEN-1;
	}
	else
	{
		len=count;
	}
	memset(global_buffer,0,sizeof(global_buffer));
	strcpy(global_buffer, buffer);
	global_buffer[len]='\0';
	return len;  
} 

static const struct file_operations kernel_proc_fops = {
	.owner = THIS_MODULE,
	.open = kernel_proc_open,
	.write = kernel_proc_write,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init kernel_proc_init(void) {
 root_dir=proc_mkdir(DIR_NAME,NULL);
 proc_create(FILE_NAME, 0, root_dir, &kernel_proc_fops);
 return 0;
}

static void __exit kernel_proc_exit(void) {
 remove_proc_entry(FILE_NAME, root_dir);
 remove_proc_entry(DIR_NAME, NULL);
}

module_init(kernel_proc_init);
module_exit(kernel_proc_exit);
