# kernel_proc_write_read
c_kernel_proc_write_read

git clone https://github.com/LZdeSTUDIO/kernel_proc_write_read.git

cd kernel_proc_write_read

make all

su

insmod pro.ko

echo hi,kernel>/proc/lz/info

cat /proc/lz/info

rmmod proc.ko
