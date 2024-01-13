# 03_三剑客之grep

[TOC]

grep全称 Global search Regular Expression and Print out the line.

根据过滤条件（模式）来做文本逐行匹配

## 总览

```shell

#grep [options] [pattern] file 

sky92@sky92:~$ grep --help
用法: grep [选项]... PATTERN [FILE]...
在每个 FILE 或是标准输入中查找 PATTERN。
默认的 PATTERN 是一个基本正则表达式(缩写为 BRE)。
例如: grep -i 'hello world' menu.h main.c

正则表达式选择与解释:
  -E, --extended-regexp     PATTERN 是一个可扩展的正则表达式(缩写为 ERE)
  -F, --fixed-strings       PATTERN 是一组由断行符分隔的字符串。
  -G, --basic-regexp        PATTERN 是一个基本正则表达式(缩写为 BRE)
  -P, --perl-regexp         PATTERN 是一个 Perl 正则表达式
  -e, --regexp=PATTERN      用 PATTERN 来进行匹配操作
  -f, --file=FILE           从 FILE 中取得 PATTERN
  -i, --ignore-case         忽略大小写
  -w, --word-regexp         强制 PATTERN 仅完全匹配字词
  -x, --line-regexp         强制 PATTERN 仅完全匹配一行
  -z, --null-data           一个 0 字节的数据行，但不是空行

杂项:
  -s, --no-messages         不显示错误信息
  -v, --invert-match        选中不匹配的行
  -V, --version             显示版本信息并退出
      --help                显示此帮助并退出

输出控制:
  -m, --max-count=NUM       NUM 次匹配后停止
  -b, --byte-offset         输出的同时打印字节偏移
  -n, --line-number         输出的同时打印行号
      --line-buffered       每行输出清空
  -H, --with-filename       为每一匹配项打印文件名
  -h, --no-filename         输出时不显示文件名前缀
      --label=LABEL         将LABEL 作为标准输入文件名前缀
  -o, --only-matching       只显示匹配PATTERN 部分的行
  -q, --quiet, --silent     不显示所有常规输出
      --binary-files=TYPE   设定二进制文件的TYPE 类型；
                            TYPE 可以是`binary', `text', 或`without-match'
  -a, --text                等同于 --binary-files=text
  -I                        等同于 --binary-files=without-match
  -d, --directories=ACTION  读取目录的方式；
                            ACTION 可以是`read', `recurse',或`skip'
  -D, --devices=ACTION      读取设备、先入先出队列、套接字的方式；
                            ACTION 可以是`read'或`skip'
  -r, --recursive           等同于--directories=recurse
  -R, --dereference-recursive       同上，但遍历所有符号链接
      --include=FILE_PATTERN  只查找匹配FILE_PATTERN 的文件
      --exclude=FILE_PATTERN  跳过匹配FILE_PATTERN 的文件和目录
      --exclude-from=FILE   跳过所有除FILE 以外的文件
      --exclude-dir=PATTERN  跳过所有匹配PATTERN 的目录。
  -L, --files-without-match  只打印不匹配FILEs 的文件名
  -l, --files-with-matches  只打印匹配FILES 的文件名
  -c, --count               只打印每个FILE 中的匹配行数目
  -T, --initial-tab         行首tabs 分隔（如有必要）
  -Z, --null                在FILE 文件最后打印空字符

文件控制:
  -B, --before-context=NUM  打印文本及其前面NUM 行
  -A, --after-context=NUM   打印文本及其后面NUM 行
  -C, --context=NUM         打印NUM 行输出文本
  -NUM                      等同于 --context=NUM
      --color[=WHEN],
      --colour[=WHEN]       使用标记高亮匹配字串；
                            WHEN 可以是`always', `never'或`auto'
  -U, --binary              不要清除行尾的CR 字符(MSDOS/Windows)
  -u, --unix-byte-offsets   忽略CR 字符，报告字节偏移
                             (MSDOS/Windows)

'egrep' 即'grep -E'。'fgrep' 即'grep -F'。
直接调用'egrep' 或是'fgrep' 均已被废弃。
若FILE 为 -，将读取标准输入。不带FILE，读取当前目录，除非命令行中指定了-r 选项。
如果少于两个FILE 参数，就要默认使用-h 参数。
如果有任意行被匹配，那退出状态为 0，否则为 1；
如果有错误产生，且未指定 -q 参数，那退出状态为 2。

请将错误报告给: bug-grep@gnu.org。翻译问题请报告至:Chinese (simplified) <i18n-zh@googlegroups.com>。
GNU grep 主页: <http://www.gnu.org/software/grep/>
GNU 软件的通用帮助: <http://www.gnu.org/gethelp/>

```

## 案例1

```shell
#建立一个文件
sky92@sky92:~$ cat /etc/passwd > /tmp/pwd.txt
#找出带有root行
sky92@sky92:~$ grep -i 'root' /tmp/pwd.txt
root:x:0:0:root:/root:/bin/bash 
#找出带有root行，显示行号
sky92@sky92:~$ grep -in 'root' /tmp/pwd.txt
1:root:x:0:0:root:/root:/bin/bash
#找出带有root行，显示行号
sky92@sky92:~$ grep 'root' /tmp/pwd.txt -i -n
1:root:x:0:0:root:/root:/bin/bash
#找出带有root行，显示行号
sky92@sky92:~$ grep 'root' /tmp/pwd.txt -in
1:root:x:0:0:root:/root:/bin/bash
# 查看总行数
sky92@sky92:~$ grep 'bin' /tmp/pwd.txt  -c
56 
```

## 案例2

建立文件/tmp/test.txt  如下 ：

```txt
I like linux

I have a NAS
I have a PC.

I have learn linux.

the website is https://space.bilibili.com/5548363
```

```shell
#cat查看 显示行数
sky92@sky92:~$ cat -n /tmp/test.txt
     1  I like linux
     2
     3  I have a NAS
     4  I have a PC.
     5
     6  I have learn linux.
     7
     8  the website is https://space.bilibili.com/5548363
     9
    10  #note
    11
```



### 使用grep操作BRE

```shell
#找出所有非空行
sky92@sky92:~$ grep '^$' /tmp/test.txt -n
2:
5:
7:
9:
11:
 
#找出非空行
sky92@sky92:~$ grep '^$' /tmp/test.txt -v
I like linux
I have a NAS
I have a PC.
I have learn linux.
the website is https://space.bilibili.com/5548363
#note
  
sky92@sky92:~$ grep '^$' /tmp/test.txt -vn
1:I like linux
3:I have a NAS
4:I have a PC.
6:I have learn linux.
8:the website is https://space.bilibili.com/5548363
10:#note

#找出非#开头的行
sky92@sky92:~$ grep '^#' /tmp/test.txt -vn
1:I like linux
2:
3:I have a NAS
4:I have a PC.
5:
6:I have learn linux.
7:
8:the website is https://space.bilibili.com/5548363
9:
11:

#找出非#开头的 非空行
sky92@sky92:~$ grep '^#' /tmp/test.txt -vn |grep '^$' /tmp/test.txt -vn
1:I like linux
3:I have a NAS
4:I have a PC.
6:I have learn linux.
8:the website is https://space.bilibili.com/5548363
10:#note
 
#找出I开头的行
sky92@sky92:~$ grep '^I' /tmp/test.txt -n
1:I like linux
3:I have a NAS
4:I have a PC.
6:I have learn linux.

#找出t开头的行
sky92@sky92:~$ grep '^t' /tmp/test.txt -n
8:the website is https://space.bilibili.com/5548363


sky92@sky92:~$ grep '.$' /tmp/test.txt -n
1:I like linux
3:I have a NAS
4:I have a PC.
6:I have learn linux.
8:the website is https://space.bilibili.com/5548363
10:#note

#找到.结尾  这里需要转义
sky92@sky92:~$ grep '\.$' /tmp/test.txt -n
4:I have a PC.
6:I have learn linux.

sky92@sky92:~$ grep '/bin/bash' /tmp/pwd.txt -n 
1:root:x:0:0:root:/root:/bin/bash
40:sky92:x:1000:1000:sky92,,,:/home/sky92:/bin/bash

sky92@sky92:~$ grep '/bin/bash' /tmp/pwd.txt  -no
1:/bin/bash
40:/bin/bash

 
#对linux系统来说 文本的行结尾有个隐藏的$ 表达换行
sky92@sky92:~$ cat -En /tmp/test.txt
     1  I like linux$
     2  $
     3  I have a NAS$
     4  I have a PC.$
     5  $
     6  I have learn linux.$
     7  $
     8  the website is https://space.bilibili.com/5548363$
     9  $
    10  #note$
    11  $

sky92@sky92:~$ grep '.' /tmp/test.txt  -n
1:I like linux
3:I have a NAS
4:I have a PC.
6:I have learn linux.
8:the website is https://space.bilibili.com/5548363
10:#note


sky92@sky92:~$ grep '.x' /tmp/test.txt  -n
1:I like linux
6:I have learn linux.

#全部匹配
sky92@sky92:~$ grep '.*' /tmp/test.txt  -n
1:I like linux
2:
3:I have a NAS
4:I have a PC.
5:
6:I have learn linux.
7:
8:the website is https://space.bilibili.com/5548363
9:
10:#note
11:

#贪婪匹配  得到有a的行 且匹配每行最后一个a之前的所有内容
sky92@sky92:~$ grep '.*a' /tmp/test.txt  -n
3:I have a NAS
4:I have a PC.
6:I have learn linux.
8:the website is https://space.bilibili.com/5548363

#贪婪匹配  得到有t的行 且匹配每行最后一个t之前的所有内容
sky92@sky92:~$ grep '.*t' /tmp/test.txt  -n
8:the website is https://space.bilibili.com/5548363
10:#note
sky92@sky92:~$ grep '.*t' /tmp/test.txt  -no
8:the website is htt
10:#not

sky92@sky92:~$ grep '[0-9]' /tmp/test.txt  -n
8:the website is https://space.bilibili.com/5548363

sky92@sky92:~$ grep '[A-Z0-9]' /tmp/test.txt  -n
1:I like linux
3:I have a NAS
4:I have a PC.
6:I have learn linux.
8:the website is https://space.bilibili.com/5548363



 
```

### 使用grep操作ERE

```shell
sky92@sky92:~$ grep -E 'i+' /tmp/test.txt  -n
1:I like linux
6:I have learn linux.
8:the website is https://space.bilibili.com/5548363

sky92@sky92:~$ grep -E 'ha+' /tmp/test.txt  -n
3:I have a NAS
4:I have a PC.
6:I have learn linux.

#i 字符匹配0次或1次 
sky92@sky92:~$ grep -E 'li?' /tmp/test.txt  -n
1:I like linux
6:I have learn linux.
8:the website is https://space.bilibili.com/5548363

sky92@sky92:~$ grep -E 'ht?ps' /tmp/test.txt  -n
sky92@sky92:~$ grep -E 'h?ps' /tmp/test.txt  -n
8:the website is https://space.bilibili.com/5548363


sky92@sky92:~$ find /tmp/ -name '*.txt' 
/tmp/path.txt
/tmp/test.txt
/tmp/pwd.txt 
 
sky92@sky92:~$ find /tmp/ -name '*.txt' | grep -E 'w|s'
/tmp/test.txt
/tmp/pwd.txt 

#匹配learn 或者lin
sky92@sky92:~$ grep -E 'l(ear|i)n' /tmp/test.txt -n
1:I like linux
6:I have learn linux.
sky92@sky92:~$ grep -E 'learn|lin' /tmp/test.txt -n
1:I like linux
6:I have learn linux.

#找到有b开头i结尾的串 并向后增加一次匹配  即对串匹配两次
sky92@sky92:~$ grep -E '(b..i).*\1' /tmp/test.txt -n
8:the website is https://space.bilibili.com/5548363


sky92@sky92:~$ grep -E 't{1,2}' /tmp/test.txt -n
8:the website is https://space.bilibili.com/5548363
10:#note
sky92@sky92:~$ grep -E 't{,2}' /tmp/test.txt -no
8:t
8:t
8:tt
10:t
sky92@sky92:~$ grep -E 't{2,}' /tmp/test.txt -no
8:tt

 
```









