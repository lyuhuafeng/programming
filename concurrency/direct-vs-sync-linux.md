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
