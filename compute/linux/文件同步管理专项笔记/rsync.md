# Rsync工具



[toc]

sky92@sky92:~$

sky92@sky92-virtual-machine:~$

## 一、安装

```bash

#centos
sky92@sky92-virtual-machine:~$ sodu yum install rsync -y

#ubuntu
sky92@sky92-virtual-machine:~$ sudo apt-get install rsync

#启动
sky92@sky92-virtual-machine:~$ sudo systemctl start rsync

#开机自启动
sky92@sky92-virtual-machine:~$ sudo systemctl enable rsync

#默认端口 tcp  873 查看端口
sky92@sky92-virtual-machine:~$ sudo netstat -tlnp

#help
sky92@sky92-virtual-machine:~$ rsync -h
rsync  version 3.2.3  protocol version 31
Copyright (C) 1996-2020 by Andrew Tridgell, Wayne Davison, and others.
Web site: https://rsync.samba.org/
Capabilities:
    64-bit files, 64-bit inums, 64-bit timestamps, 64-bit long ints,
    socketpairs, hardlinks, hardlink-specials, symlinks, IPv6, atimes,
    batchfiles, inplace, append, ACLs, xattrs, optional protect-args, iconv,
    symtimes, prealloc, stop-at, no crtimes
Optimizations:
    SIMD, no asm, openssl-crypto
Checksum list:
    xxh128 xxh3 xxh64 (xxhash) md5 md4 none
Compress list:
    zstd lz4 zlibx zlib none

rsync comes with ABSOLUTELY NO WARRANTY.  This is free software, and you
are welcome to redistribute it under certain conditions.  See the GNU
General Public Licence for details.

rsync is a file transfer program capable of efficient remote update
via a fast differencing algorithm.

Usage: rsync [OPTION]... SRC [SRC]... DEST
  or   rsync [OPTION]... SRC [SRC]... [USER@]HOST:DEST
  or   rsync [OPTION]... SRC [SRC]... [USER@]HOST::DEST
  or   rsync [OPTION]... SRC [SRC]... rsync://[USER@]HOST[:PORT]/DEST
  or   rsync [OPTION]... [USER@]HOST:SRC [DEST]
  or   rsync [OPTION]... [USER@]HOST::SRC [DEST]
  or   rsync [OPTION]... rsync://[USER@]HOST[:PORT]/SRC [DEST]
The ':' usages connect via remote shell, while '::' & 'rsync://' usages connect
to an rsync daemon, and require SRC or DEST to start with a module name.

Options
--verbose, -v            increase verbosity
--info=FLAGS             fine-grained informational verbosity
--debug=FLAGS            fine-grained debug verbosity
--stderr=e|a|c           change stderr output mode (default: errors)
--quiet, -q              suppress non-error messages
--no-motd                suppress daemon-mode MOTD
--checksum, -c           skip based on checksum, not mod-time & size
--archive, -a            archive mode is -rlptgoD (no -A,-X,-U,-N,-H)
--no-OPTION              turn off an implied OPTION (e.g. --no-D)
--recursive, -r          recurse into directories
--relative, -R           use relative path names
--no-implied-dirs        don't send implied dirs with --relative
--backup, -b             make backups (see --suffix & --backup-dir)
--backup-dir=DIR         make backups into hierarchy based in DIR
--suffix=SUFFIX          backup suffix (default ~ w/o --backup-dir)
--update, -u             skip files that are newer on the receiver
--inplace                update destination files in-place
--append                 append data onto shorter files
--append-verify          --append w/old data in file checksum
--dirs, -d               transfer directories without recursing
--mkpath                 create the destination's path component
--links, -l              copy symlinks as symlinks
--copy-links, -L         transform symlink into referent file/dir
--copy-unsafe-links      only "unsafe" symlinks are transformed
--safe-links             ignore symlinks that point outside the tree
--munge-links            munge symlinks to make them safe & unusable
--copy-dirlinks, -k      transform symlink to dir into referent dir
--keep-dirlinks, -K      treat symlinked dir on receiver as dir
--hard-links, -H         preserve hard links
--perms, -p              preserve permissions
--executability, -E      preserve executability
--chmod=CHMOD            affect file and/or directory permissions
--acls, -A               preserve ACLs (implies --perms)
--xattrs, -X             preserve extended attributes
--owner, -o              preserve owner (super-user only)
--group, -g              preserve group
--devices                preserve device files (super-user only)
--copy-devices           copy device contents as regular file
--specials               preserve special files
-D                       same as --devices --specials
--times, -t              preserve modification times
--atimes, -U             preserve access (use) times
--open-noatime           avoid changing the atime on opened files
--crtimes, -N            preserve create times (newness)
--omit-dir-times, -O     omit directories from --times
--omit-link-times, -J    omit symlinks from --times
--super                  receiver attempts super-user activities
--fake-super             store/recover privileged attrs using xattrs
--sparse, -S             turn sequences of nulls into sparse blocks
--preallocate            allocate dest files before writing them
--write-devices          write to devices as files (implies --inplace)
--dry-run, -n            perform a trial run with no changes made
--whole-file, -W         copy files whole (w/o delta-xfer algorithm)
--checksum-choice=STR    choose the checksum algorithm (aka --cc)
--one-file-system, -x    don't cross filesystem boundaries
--block-size=SIZE, -B    force a fixed checksum block-size
--rsh=COMMAND, -e        specify the remote shell to use
--rsync-path=PROGRAM     specify the rsync to run on remote machine
--existing               skip creating new files on receiver
--ignore-existing        skip updating files that exist on receiver
--remove-source-files    sender removes synchronized files (non-dir)
--del                    an alias for --delete-during
--delete                 delete extraneous files from dest dirs
--delete-before          receiver deletes before xfer, not during
--delete-during          receiver deletes during the transfer
--delete-delay           find deletions during, delete after
--delete-after           receiver deletes after transfer, not during
--delete-excluded        also delete excluded files from dest dirs
--ignore-missing-args    ignore missing source args without error
--delete-missing-args    delete missing source args from destination
--ignore-errors          delete even if there are I/O errors
--force                  force deletion of dirs even if not empty
--max-delete=NUM         don't delete more than NUM files
--max-size=SIZE          don't transfer any file larger than SIZE
--min-size=SIZE          don't transfer any file smaller than SIZE
--max-alloc=SIZE         change a limit relating to memory alloc
--partial                keep partially transferred files
--partial-dir=DIR        put a partially transferred file into DIR
--delay-updates          put all updated files into place at end
--prune-empty-dirs, -m   prune empty directory chains from file-list
--numeric-ids            don't map uid/gid values by user/group name
--usermap=STRING         custom username mapping
--groupmap=STRING        custom groupname mapping
--chown=USER:GROUP       simple username/groupname mapping
--timeout=SECONDS        set I/O timeout in seconds
--contimeout=SECONDS     set daemon connection timeout in seconds
--ignore-times, -I       don't skip files that match size and time
--size-only              skip files that match in size
--modify-window=NUM, -@  set the accuracy for mod-time comparisons
--temp-dir=DIR, -T       create temporary files in directory DIR
--fuzzy, -y              find similar file for basis if no dest file
--compare-dest=DIR       also compare destination files relative to DIR
--copy-dest=DIR          ... and include copies of unchanged files
--link-dest=DIR          hardlink to files in DIR when unchanged
--compress, -z           compress file data during the transfer
--compress-choice=STR    choose the compression algorithm (aka --zc)
--compress-level=NUM     explicitly set compression level (aka --zl)
--skip-compress=LIST     skip compressing files with suffix in LIST
--cvs-exclude, -C        auto-ignore files in the same way CVS does
--filter=RULE, -f        add a file-filtering RULE
-F                       same as --filter='dir-merge /.rsync-filter'
                         repeated: --filter='- .rsync-filter'
--exclude=PATTERN        exclude files matching PATTERN
--exclude-from=FILE      read exclude patterns from FILE
--include=PATTERN        don't exclude files matching PATTERN
--include-from=FILE      read include patterns from FILE
--files-from=FILE        read list of source-file names from FILE
--from0, -0              all *-from/filter files are delimited by 0s
--protect-args, -s       no space-splitting; wildcard chars only
--copy-as=USER[:GROUP]   specify user & optional group for the copy
--address=ADDRESS        bind address for outgoing socket to daemon
--port=PORT              specify double-colon alternate port number
--sockopts=OPTIONS       specify custom TCP options
--blocking-io            use blocking I/O for the remote shell
--outbuf=N|L|B           set out buffering to None, Line, or Block
--stats                  give some file-transfer stats
--8-bit-output, -8       leave high-bit chars unescaped in output
--human-readable, -h     output numbers in a human-readable format
--progress               show progress during transfer
-P                       same as --partial --progress
--itemize-changes, -i    output a change-summary for all updates
--remote-option=OPT, -M  send OPTION to the remote side only
--out-format=FORMAT      output updates using the specified FORMAT
--log-file=FILE          log what we're doing to the specified FILE
--log-file-format=FMT    log updates using the specified FMT
--password-file=FILE     read daemon-access password from FILE
--early-input=FILE       use FILE for daemon's early exec input
--list-only              list the files instead of copying them
--bwlimit=RATE           limit socket I/O bandwidth
--stop-after=MINS        Stop rsync after MINS minutes have elapsed
--stop-at=y-m-dTh:m      Stop rsync at the specified point in time
--write-batch=FILE       write a batched update to FILE
--only-write-batch=FILE  like --write-batch but w/o updating dest
--read-batch=FILE        read a batched update from FILE
--protocol=NUM           force an older protocol version to be used
--iconv=CONVERT_SPEC     request charset conversion of filenames
--checksum-seed=NUM      set block/file checksum seed (advanced)
--ipv4, -4               prefer IPv4
--ipv6, -6               prefer IPv6
--version, -V            print the version + other info and exit
--help, -h (*)           show this help (* -h is help only on its own)

Use "rsync --daemon --help" to see the daemon-mode command-line options.
Please see the rsync(1) and rsyncd.conf(5) man pages for full documentation.
See https://rsync.samba.org/ for updates, bug reports, and answers
rsync error: syntax or usage error (code 1) at main.c(1735) [client=3.2.3]


#rsync基本格式
#rsync [-参数]  [源文件地址]  [目标文件地址]


```



## 本地文件夹之间的同步



```bash
#两个目录
目录A：/tmp/foldera 
目录B：/tmp/folderb 
#两个文件
文件A：/tmp/foldera/filea
文件B：/tmp/folderb/fileb
#将目录A下的内容备份到目录B下  注意这里的foldera后面需要/ 否则整个目录A会被作为整体放到目录B下
sky92@sky92-virtual-machine:/tmp$ rsync -a /tmp/foldera/ /tmp/folderb

#可见过程的同步  可见文件A被同步
sky92@sky92-virtual-machine:/tmp$ rsync -av /tmp/foldera/ /tmp/folderb
sending incremental file list
./
filea

sent 121 bytes  received 38 bytes  318.00 bytes/sec
total size is 0  speedup is 0.00
 
#再次同步  可见已经不同步了
sky92@sky92-virtual-machine:/tmp$ rsync -av /tmp/foldera/ /tmp/folderb
sending incremental file list

sent 75 bytes  received 12 bytes  174.00 bytes/sec
total size is 0  speedup is 0.00

#修改文件A后再次同步
sky92@sky92-virtual-machine:/tmp$ rsync -av /tmp/foldera/ /tmp/folderb
sending incremental file list
./
filea

sent 144 bytes  received 38 bytes  364.00 bytes/sec
total size is 16  speedup is 0.09
 


```



## 远程同步 

准备两台LINUX主机

主机1的IP：192.168.35.128

主机2的IP：192.168.35.131

### 方法一

rsync通过ssh的scp服务进行工作

```bash
################主机1操作################
# 新版本的rsync默认使用ssh  所以这里的 -e指定协议的参数 可以省略
sky92@sky92-virtual-machine:/tmp$ rsync -av -e "ssh -p 22" /tmp/foldera/ sky92@192.168.35.131:/tmp/folderc
sky92@192.168.35.131's password:
sending incremental file list
./
filea

sent 144 bytes  received 38 bytes  52.00 bytes/sec
total size is 16  speedup is 0.09


###############此时进入主机2  文件已同步##############
sky92@sky92-virtual-machine:/tmp/folderc$ ls
filea
  
```

 

### 方法二 

模组同步需要监听服务器安装rsync 并运行rsyncd进程，默认监听端口为873，数据不经过加密传输；

```bash
##############在主机1上配置模组##############

#模组同步需要配置文件 rsyncd.conf 
sky92@sky92-virtual-machine:/tmp$ locate rsyncd| grep conf
/usr/share/doc/rsync/examples/rsyncd.conf
/usr/share/man/man5/rsyncd.conf.5.gz
#文件在 /etc/rsyncd.conf若无则自己创建一个 
sky92@sky92-virtual-machine:/tmp$ sudo nano rsyncd.conf

#rsyncd.conf填入
uid = sky92
gid = sky92
[test123]
path=/tmp/test	#同步位置
list = yes		#现实模组
read only = no	#只读
ignore errors	#忽略错误

################进入主机2#####################
#查看模组
sky92@sky92-virtual-machine:/tmp/folderc$ rsync 192.168.35.128::
test123
#查看模组下文件名称
sky92@sky92-virtual-machine:/tmp/folderc$ rsync 192.168.35.128::test123
drwxrwxr-x          4,096 2022/10/25 17:08:45 .
-rw-rw-r--              0 2022/10/25 17:08:37 filexx
-rw-rw-r--              0 2022/10/25 17:08:45 filexx1513893
-rw-rw-r--              0 2022/10/25 17:08:40 filexx54684

#######拉取########
#拉取主机1的文件到主机2上
sky92@sky92-virtual-machine:/tmp/folderc$ rsync -av 192.168.35.128::test123 /tmp/folderc/
receiving incremental file list
./
filexx
filexx1513893
filexx54684

sent 84 bytes  received 236 bytes  640.00 bytes/sec
total size is 0  speedup is 0.00

sky92@sky92-virtual-machine:/tmp/folderc$ ls -al
总用量 12
drwxrwxr-x  2 sky92 sky92 4096 10月 25 17:08 ./
drwxrwxrwt 17 root  root  4096 10月 25 17:10 ../
-rw-rw-r--  1 sky92 sky92   16 10月 25 16:41 filea
-rw-rw-r--  1 sky92 sky92    0 10月 25 17:08 filexx
-rw-rw-r--  1 sky92 sky92    0 10月 25 17:08 filexx1513893
-rw-rw-r--  1 sky92 sky92    0 10月 25 17:08 filexx54684

########推送#######
#推送主机2的文件到主机1上
#若主机1没有配置 uid 和 gid 推送会有权限问题  
sky92@sky92-virtual-machine:/tmp/testx$ sudo rsync -av /tmp/testx/ 192.168.35.128::test123
sending incremental file list
rsync: [generator] failed to set times on "/." (in test123): Operation not permitted (1)
./
gogogo
rsync: [receiver] mkstemp "/.gogogo.6giGgq" (in test123) failed: Permission denied (13)

sent 185 bytes  received 223 bytes  816.00 bytes/sec
total size is 0  speedup is 0.00
rsync error: some files/attrs were not transferred (see previous errors) (code 23) at main.c(1333) [sender=3.2.3]
#正确操作
sky92@sky92-virtual-machine:/tmp/testx$ sudo rsync -av /tmp/testx/ 192.168.35.128::test123
sending incremental file list
./
gogogo

sent 185 bytes  received 38 bytes  446.00 bytes/sec
total size is 0  speedup is 0.00
 


```

### 模组同步的密码设置



```bash

##############在主机1上配置模组##############
sky92@sky92-virtual-machine:/etc$ sudo mkdir rsyncd
#密码文件创建
sky92@sky92-virtual-machine:/etc/rsyncd$ touch /etc/rsyncd/rsyncd.secrets

sky92@sky92-virtual-machine:/tmp$ sudo nano rsyncd.conf

#rsyncd.conf填入
uid = root
gid = root

secrets file = /etc/rsyncd/rsyncd.secrets

[test123]
path=/tmp/test	#同步位置
list = yes		#现实模组
read only = no	#只读
ignore errors	#忽略错误
auth users = sky92

#建立密码文件
sky92@sky92-virtual-machine:/etc/rsyncd$ sudo nano rsyncd.secrets
sky92@sky92-virtual-machine:/etc/rsyncd$ sudo chmod 600 rsyncd.secrets
 
#/etc/rsyncd/rsyncd.secrets 填入
sky92:123456



################进入主机2#####################
sky92@sky92-virtual-machine:/etc$ rsync sky92@192.168.35.128::test123
Password:
drwxrwxr-x          4,096 2022/10/25 17:13:42 .
-rw-rw-r--              0 2022/10/25 17:08:37 filexx
-rw-rw-r--              0 2022/10/25 17:08:45 filexx1513893
-rw-rw-r--              0 2022/10/25 17:08:40 filexx54684
-rw-rw-r--              0 2022/10/25 17:13:42 gogogo
 

```



### 把密码在客户端保存

```bash
################进入主机2#####################
sky92@sky92-virtual-machine:/etc$ sudo touch rsync.password
sky92@sky92-virtual-machine:/etc$ sudo nano rsync.password
#直接在文件中填入明文密码 设置权限
sky92@sky92-virtual-machine:/etc$ sudo chmod 600 rsync.password

#然后就可以使用了
sky92@sky92-virtual-machine:/etc$ sudo rsync --password-file=/etc/rsync.password sky92@192.168.35.128::test123
drwxrwxr-x          4,096 2022/10/25 17:13:42 .
-rw-rw-r--              0 2022/10/25 17:08:37 filexx
-rw-rw-r--              0 2022/10/25 17:08:45 filexx1513893
-rw-rw-r--              0 2022/10/25 17:08:40 filexx54684
-rw-rw-r--              0 2022/10/25 17:13:42 gogogo

#推送
sky92@sky92-virtual-machine:/etc$ sudo rsync -av --password-file=/etc/rsync.password /tmp/testx/ sky92@192.168.35.128::test123
sending incremental file list
./
file39384762394

sent 215 bytes  received 38 bytes  506.00 bytes/sec
total size is 0  speedup is 0.00


```











