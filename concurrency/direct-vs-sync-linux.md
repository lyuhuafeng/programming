on stackoverflow:
https://stackoverflow.com/questions/19440041/o-direct-vs-o-sync-on-linux-freebsd/

https://stackoverflow.com/questions/41257656/what-does-o-direct-really-mean/49462406#49462406

// linux
       O_DIRECT (since Linux 2.4.10)
              Try to minimize cache effects of the I/O to and from this
              file.  In general this will degrade performance, but it is
              useful in special situations, such as when applications do
              their own caching.  File I/O is done directly to/from
              user-space buffers.  The O_DIRECT flag on its own makes an
              effort to transfer data synchronously, but does not give
              the guarantees of the O_SYNC flag that data and necessary
              metadata are transferred.  To guarantee synchronous I/O,
              O_SYNC must be used in addition to O_DIRECT.  See NOTES
              below for further discussion.

              A semantically similar (but deprecated) interface for
              block devices is described in raw(8).

// freebsd
       O_DIRECT	may be used to minimize	or  eliminate  the  cache  effects  of
       reading and writing.  The system	will attempt to	avoid caching the data
       you  read or write.  If it cannot avoid caching the data, it will mini-
       mize the	impact the data	has on the cache.  Use of this flag can	 dras-
       tically reduce performance if not used with care.

# Synchronized I/O

POSIX.1-2008 "synchronized I/O" option，定义了若干 synchronized I/O 变种。

open() 的 O_SYNC, O_DSYNC, and O_RSYNC

Linux implements O_SYNC and O_DSYNC

O_SYNC：提供 synchronized I/O <font color=green>file</font> integrity completion，意思是，write 操作将把 data flush 到硬件，也把所有相关 metadata 也 flush 到硬件中。

O_DSYNC：提供 synchronized I/O <font color=green>data</font> integrity completion, 意思是，write 操作把 data flush 到硬件，但只把不影响接下来的 read 操作的 metadata 刷到硬件中。

例，两个 metadata，文件长度、文件最后修改时间。所有写操作都更新「文件最后修改时间」，但只有 append 写操作才更新「文件长度」。O_DSYNC 保证更新「文件长度」，不保证更新「文件最后修改时间」。

#

O_DIRECT:

linux下：若文件 `open()` 时指定了 `O_DIRECT` 选项，则从该文件 `read()` 时，对 buffer 的起始地址、长度，以及文件 offset 均可能有 alignment 要求。

linux下，该要求与 file system 和 kernel 版本有关系。没有统一接口来查询具体的alignment要求。

2.6后，alignment to 512-byte boundaries 应该足够了。
方法一：可用 posix_memalign() 分配buffer，来满足alignment要求。
方法二：`static char buffer[512] __attribute__ ((__aligned__ (512)));`  未试过
方法三：if you're using x86, you could use the `<mm_malloc.h>` intrinsic support functions: _mm_malloc and _mm_free. 没试过

FreeBSD下，O_DIRECT 没有 alignment 要求！

linux:

Providing the O_DIRECT flag to open() instructs the kernel to minimize the presence of I/O management. When this flag is provided, I/O will initiate directly from user-space buffers to the device, bypassing the page cache. All I/O will be synchronous; operations will not return until completed.

When performing direct I/O, the request length, buffer alignment, and file offsets must all be integer multiples of the underlying device’s sector size—generally, this is 512 bytes.

Before the 2.6 Linux kernel, this requirement was stricter: in 2.4, everything must be aligned on the filesystem’s logical block size (often 4 KB). To remain compatible, applications should align to the larger (and potentially less convenient) logical block size.
    


--------------------------------------------------------------------------------------------

使用传统的大文件接口(open64, lseek64等及其配套数据类型off64_t)要在包含头文件之前定义宏_LARGEFILE64_SOURCE。
现在一般不建议直接使用这些接口，而是先定义宏_FILE_OFFSET_BITS=64，再直接使用普通的open, lseek, off_t等，编译链接时会自动把它们转换成open64, lseek64, off64_t等。
-D_LARGEFILE64_SOURCE
或者干脆
-D_GNU_SOURCE，把所有特性全打开
man feature_test_macros
