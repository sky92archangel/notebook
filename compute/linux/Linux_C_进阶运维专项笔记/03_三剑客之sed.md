# 03_三剑客之sed

[TOC]

sed awk中字符串要用单引号，双引号有其他用处；

sed 对文件数据流加工处理，sed = Stream Editor，是操作过滤转换文本的工具；

常用功能有结合正则表达对文件实现快速增删改查其中查询的功能常用的是过滤和取出行；

每次读入一行，在内存中做模式匹配；成功后显示到屏幕；

```shell
#sed [选项]  [内置命令字符] [输入文件]

sky92@sky92:~$ sed --help
用法: sed [选项]... {脚本(如果没有其他脚本)} [输入文件]...

  -n, --quiet, --silent
                 取消自动打印模式空间（未处理过的数据不显示）
  -e 脚本, --expression=脚本
                 添加“脚本”到程序的运行列表 添加多规则
  -f 脚本文件, --file=脚本文件
                 添加“脚本文件”到程序的运行列表
  --follow-symlinks
                 直接修改文件时跟随软链接
  -i[SUFFIX], --in-place[=SUFFIX]
                 edit files in place (makes backup if SUFFIX supplied) 写入文件
  -l N, --line-length=N
                 指定“l”命令的换行期望长度
  --posix
                 关闭所有 GNU 扩展
  -r, --regexp-extended
                 在脚本中使用扩展正则表达式
  -s, --separate
                 将输入文件视为各个独立的文件而不是一个长的连续输入
  -u, --unbuffered
                 从输入文件读取最少的数据，更频繁的刷新输出
  -z, --null-data
                 separate lines by NUL characters
      --help     打印帮助并退出
      --version  输出版本信息并退出

如果没有 -e, --expression, -f 或 --file 选项，那么第一个非选项参数被视为
sed脚本。其他非选项参数被视为输入文件，如果没有输入文件，那么程序将从标准
输入读取数据。

GNU版sed主页： <http://www.gnu.org/software/sed/>。
使用GNU软件所需帮助文档： <http://www.gnu.org/gethelp/>。
将错误报告通过电子邮件发送到：<bug-sed@gnu.org>.
请务必将单词“sed”放在标题的某处。
 
```



## sed内置命令符

| 内置命令符            | 解释                                      |
| --------------------- | ----------------------------------------- |
| a                     | append 追加文本 在指定行后加一行          |
| d                     | delete 删除匹配行                         |
| i                     | insert 插入文本，在指定行前添加一行       |
| p                     | print 打印匹配内容 通常和 -n 一起使用     |
| s/正则表达式/新内容/g | 匹配正则内容 然后替换 结尾的g代表全局匹配 |
|                       |                                           |

## 案例

建立文件/tmp/test2.txt  如下 ：

```txt
I like linux
I have a NAS
I have a PC.
I have learn linux.
the website is https://space.bilibili.com/5548363
#note
gooooooood
```

```shell
sky92@sky92:~$ cat -n /tmp/test2.txt
     1  I like linux
     2  I have a NAS
     3  I have a PC.
     4  I have learn linux.
     5  the website is https://space.bilibili.com/5548363
     6  #note
     7  gooooooood
```



sed操作

```shell
#找到第2和第3行 但是无论是否处理都显示 凡是处理的都会多出来一行
sky92@sky92:~$ sed '2,3p' /tmp/test2.txt
I like linux
I have a NAS
I have a NAS
I have a PC.
I have a PC.
I have learn linux.
the website is https://space.bilibili.com/5548363
#note
gooooooood

#找到第2和第3行
sky92@sky92:~$ sed '2,3p' /tmp/test2.txt -n
I have a NAS
I have a PC.

#找到第2和接下来的3行
sky92@sky92:~$ sed '2,+3p' /tmp/test2.txt -n
I have a NAS
I have a PC.
I have learn linux.
the website is https://space.bilibili.com/5548363

#找出有linux的行
sky92@sky92:~$ sed '/linux/p' /tmp/test2.txt -n
I like linux
I have learn linux.

#删除有have的行
sky92@sky92:~$ sed '/have/d' /tmp/test2.txt
I like linux
the website is https://space.bilibili.com/5548363
#note
gooooooood

#删除从第4行到结尾的所有内容
sky92@sky92:~$ sed '4,$d' /tmp/test2.txt
I like linux
I have a NAS
I have a PC.

#全局替换linux 
sky92@sky92:~$ sed 's/linux/MacOS/' /tmp/test2.txt
I like MacOS
I have a NAS
I have a PC.
I have learn MacOS.
the website is https://space.bilibili.com/5548363
#note
gooooooood

sky92@sky92:~$ sed -e 's/I/God/g' -e 's/have/has/g' /tmp/test2.txt
God like linux
God has a NAS
God has a PC.
God has learn linux.
the website is https://space.bilibili.com/5548363
#note
gooooooood

#将句子 God likes MacOS 加入到第二行的后面作为第三行 后面内容顺延  
sky92@sky92:~$ sed '2a God likes MacOS' /tmp/test2.txt
I like linux
I have a NAS
God likes MacOS
I have a PC.
I have learn linux.
the website is https://space.bilibili.com/5548363
#note
gooooooood

#将句子 God likes MacOS 加入到第二行的前面作为第二行 后面内容顺延  
sky92@sky92:~$ sed '2i God likes MacOS' /tmp/test2.txt
I like linux
God likes MacOS
I have a NAS
I have a PC.
I have learn linux.
the website is https://space.bilibili.com/5548363
#note
gooooooood

sky92@sky92:~$ sed '2a God likes MacOS\nGod likes Windows' /tmp/test2.txt
I like linux
I have a NAS
God likes MacOS
God likes Windows
I have a PC.
I have learn linux.
the website is https://space.bilibili.com/5548363
#note
gooooooood

sky92@sky92:~$ sed 'a -------------' /tmp/test2.txt
I like linux
-------------
I have a NAS
-------------
I have a PC.
-------------
I have learn linux.
-------------
the website is https://space.bilibili.com/5548363
-------------
#note
-------------
gooooooood
-------------


```



## 实战

网卡信息查找，我若要获得docker的inet地址 如何使用sed处理？

```shell
sky92@sky92:~$ ifconfig
docker0   Link encap:以太网  硬件地址 02:42:4f:17:cd:6e
          inet 地址:172.17.0.1  广播:172.17.255.255  掩码:255.255.0.0
          inet6 地址: fe80::42:4fff:fe17:cd6e/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  跃点数:1
          接收数据包:19270327 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:17134167 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:0
          接收字节:11701892148 (11.7 GB)  发送字节:4092913633 (4.0 GB)

enp1s0    Link encap:以太网  硬件地址 70:85:c2:34:7d:c3
          inet 地址:192.168.1.73  广播:192.168.1.255  掩码:255.255.255.0
          inet6 地址: 240e:388:582a:5400:4cdc:a24e:291f:47a3/64 Scope:Global
          inet6 地址: 240e:388:582a:5400:60b0:1c1b:45fc:cb58/64 Scope:Global
          inet6 地址: 240e:388:582a:5400:5cd8:73ff:9988:d08e/64 Scope:Global
          inet6 地址: fe80::2014:dd4:bef6:6f02/64 Scope:Link
          inet6 地址: 240e:388:582a:5400:5095:9d35:54e5:edfb/64 Scope:Global
          UP BROADCAST RUNNING MULTICAST  MTU:1500  跃点数:1
          接收数据包:291469954 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:492625035 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:1000
          接收字节:160069484441 (160.0 GB)  发送字节:646568965502 (646.5 GB)

lo        Link encap:本地环回
          inet 地址:127.0.0.1  掩码:255.0.0.0
          inet6 地址: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  跃点数:1
          接收数据包:686535 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:686535 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:1000
          接收字节:496988429 (496.9 MB)  发送字节:496988429 (496.9 MB)

veth1568b05 Link encap:以太网  硬件地址 aa:94:42:b0:d9:a2
          inet6 地址: fe80::a894:42ff:feb0:d9a2/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  跃点数:1
          接收数据包:17797763 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:15202821 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:0
          接收字节:11693189296 (11.6 GB)  发送字节:2164155220 (2.1 GB)
 
sky92@sky92:~$ ifconfig docker0
docker0   Link encap:以太网  硬件地址 02:42:4f:17:cd:6e
          inet 地址:172.17.0.1  广播:172.17.255.255  掩码:255.255.0.0
          inet6 地址: fe80::42:4fff:fe17:cd6e/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  跃点数:1
          接收数据包:19273786 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:17138024 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:0
          接收字节:11702272901 (11.7 GB)  发送字节:4093493160 (4.0 GB)

sky92@sky92:~$ ifconfig docker0 | sed '2p' -n
          inet 地址:172.17.0.1  广播:172.17.255.255  掩码:255.255.0.0

sky92@sky92:~$ ifconfig docker0 | sed '2p' -n | sed 's/^.*地址\://g'
172.17.0.1  广播:172.17.255.255  掩码:255.255.0.0

sky92@sky92:~$ ifconfig docker0 | sed '2p' -n | sed 's/^.*地址\://g' |sed 's/广播.*$//g'
172.17.0.1

sky92@sky92:~$ ifconfig docker0 | sed -e '2s/^.*地址\://gp' -e '2s/广播.*$//gp' -n
172.17.0.1  广播:172.17.255.255  掩码:255.255.0.0
172.17.0.1

 
```













