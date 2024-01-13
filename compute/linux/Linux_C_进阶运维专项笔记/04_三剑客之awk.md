# 04_三剑客之awk

[TOC]

## 简介

awk 是强大的文本格式化工具，早期在UNIX系统上开发的，之后移植到了linux上awk是gawk = GNU awk

awk是一门脚本语言 ，有循环判断等

```shell

awk [可选参数]  '模式[动作]'  [文件数据] 

sky92@sky92:~$ awk --help
Usage: awk [POSIX or GNU style options] -f progfile [--] file ...
Usage: awk [POSIX or GNU style options] [--] 'program' file ...
POSIX options:          GNU long options: (standard)
        -f progfile             --file=progfile
        -F fs                   --field-separator=fs
        -v var=val              --assign=var=val
Short options:          GNU long options: (extensions)
        -b                      --characters-as-bytes
        -c                      --traditional
        -C                      --copyright
        -d[file]                --dump-variables[=file]
        -D[file]                --debug[=file]
        -e 'program-text'       --source='program-text'
        -E file                 --exec=file
        -g                      --gen-pot
        -h                      --help
        -i includefile          --include=includefile
        -l library              --load=library
        -L[fatal|invalid]       --lint[=fatal|invalid]
        -M                      --bignum
        -N                      --use-lc-numeric
        -n                      --non-decimal-data
        -o[file]                --pretty-print[=file]
        -O                      --optimize
        -p[file]                --profile[=file]
        -P                      --posix
        -r                      --re-interval
        -S                      --sandbox
        -t                      --lint-old
        -V                      --version

To report bugs, see node `Bugs' in `gawk.info', which is
section `Reporting Problems and Bugs' in the printed version.

gawk is a pattern scanning and processing language.
By default it reads standard input and writes standard output.

Examples:
        gawk '{ sum += $1 }; END { print sum }' file
        gawk -F: '{ print $1 }' /etc/passwd

```



## 建立测试文件

```shell
sky92@sky92:~$ echo good{1..10}  >> /tmp/awktest.txt 
sky92@sky92:~$ echo good{11..20} >> /tmp/awktest.txt
sky92@sky92:~$ echo good{21..30} >> /tmp/awktest.txt
sky92@sky92:~$ cat -n /tmp/awktest.txt
     1  good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
     2  good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
     3  good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
     4  good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ cp /tmp/awktest.txt /tmp/awktest2.txt
sky92@sky92:~$ sed 's/\ /#/gp' /tmp/awktest2.txt -i -n
sky92@sky92:~$ cat -n /tmp/awktest2.txt
     1  good1#good2#good3#good4#good5#good6#good7#good8#good9#good10
     2  good1#good2#good3#good4#good5#good6#good7#good8#good9#good10
     3  good11#good12#good13#good14#good15#good16#good17#good18#good19#good20
     4  good21#good22#good23#good24#good25#good26#good27#good28#good29#good30
 
```



## 演示

awk默认以空格为分隔符

下面仅仅打印内容

```shell
#每行取出首个
sky92@sky92:~$ awk '{print $1}' /tmp/awktest.txt
good1
good1
good11
good21

#每行取出第二个
sky92@sky92:~$ awk '{print $2}' /tmp/awktest.txt
good2
good2
good12
good22

#每行取出整行 全部打印出来
sky92@sky92:~$ awk '{print $0}' /tmp/awktest.txt
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
good21 good22 good23 good24 good25 good26 good27 good28 good29 good30
 
#  $NF 代表最后一列
sky92@sky92:~$ awk '{print $NF}' /tmp/awktest.txt
good10
good10
good20
good30

sky92@sky92:~$ awk '{print $(NF-1)}' /tmp/awktest.txt
good9
good9
good19
good29
 
```

### awk内置变量

| 内置变量 | 解释                     |
| -------- | ------------------------ |
| $n       | 当前行的第n个字段        |
| $0       | 当前行的所有             |
| FS       | 字段分割符 默认为空格    |
| NF       | 一行内分割后的总字段数量 |
| NR       | 当前记录数 行数          |
|          |                          |

### awk参数

| 参数 | 解释                      |
| ---- | ------------------------- |
| -F   | 指定分割字段符            |
| -v   | 定义或修改一个awk内部变量 |
| -f   | 从脚本文件中读取awk命令   |

### 基本用法

```shell
sky92@sky92:~$ awk '{print $1 $2 $4}' /tmp/awktest.txt
good1good2good4
good1good2good4
good11good12good14
good21good22good24

sky92@sky92:~$ awk '{print $1,$2,$4}' /tmp/awktest.txt
good1 good2 good4
good1 good2 good4
good11 good12 good14
good21 good22 good24

sky92@sky92:~$ awk '{print $3,$1,$2}' /tmp/awktest.txt
good3 good1 good2
good3 good1 good2
good13 good11 good12
good23 good21 good22

# awk需要在外层使用单引号， 内层才能用双引号
sky92@sky92:~$ awk '{print "第三列："$3,"第一列："$1}' /tmp/awktest.txt
第三列：good3 第一列：good1
第三列：good3 第一列：good1
第三列：good13 第一列：good11
第三列：good23 第一列：good21

sky92@sky92:~$ awk 'NR==3' /tmp/awktest.txt
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20

sky92@sky92:~$ awk 'NR==2,NR==4' /tmp/awktest.txt
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'NR==3{print $0}' /tmp/awktest.txt
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
sky92@sky92:~$ awk 'NR==3{print $1}' /tmp/awktest.txt
good11
sky92@sky92:~$ awk 'NR==3{print $2}' /tmp/awktest.txt
good12
sky92@sky92:~$ awk 'NR==2,NR==4{print $2}' /tmp/awktest.txt
good2
good12
good22

sky92@sky92:~$ awk '{print NR,$0}' /tmp/awktest.txt
1 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'NR==2,NR==4{print NR,$0}' /tmp/awktest.txt
2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'NR==2,NR==4{print NR,$2,$(NF-1),$(NF-2)}' /tmp/awktest.txt
2 good2 good9 good8
3 good12 good19 good18
4 good22 good29 good28


```

## 分隔符问题

输入分隔符FS      输出分隔符OFS  

```shell

sky92@sky92:~$ awk 'NR==2{print $0}' /tmp/awktest2.txt                         good1#good2#good3#good4#good5#good6#good7#good8#good9#good10 
sky92@sky92:~$ awk -F '#' 'NR==2{print $1}' /tmp/awktest2.txt
good1
sky92@sky92:~$ awk -v FS='#' 'NR==2{print $1}' /tmp/awktest2.txt
good1

# 输入分隔符FS设定为#  输出分隔符OFS设定为|  
sky92@sky92:~$ awk -v FS='#' -v OFS='|' 'NR==2{print $1,$3}' /tmp/awktest2.txt
good1|good3
# 输入分隔符FS设定为#  输出分隔符OFS设定为---  
sky92@sky92:~$ awk -v FS='#' -v OFS='---' 'NR==2{print $1,$3}' /tmp/awktest2.txt
good1---good3


```

## 内置变量

| 内置变量 | 解释                                           |
| -------- | ---------------------------------------------- |
| FS       | 输入字段分割符 默认是空格                      |
| OFS      | 输出字段分割符 默认是空格                      |
| RS       | 输入的换行符 指定输入内容的换行标识 默认是回车 |
| ORS      | 输出的换行符 指定输出内容的换行标识 默认是回车 |
| NF       | 当前行的字段数量                               |
| NR       | 行号                                           |
| FNR      | 各个文件的行号                                 |
| FILENAME | 当前文件名                                     |
| ARGC     | 命令行参数个数                                 |
| ARGV     | 数组 保存命令行给定的各个参数                  |

awk的内置变量单独使用时不需要加$符号

```shell
sky92@sky92:~$ cat -n /tmp/awktest2.txt
     1  good1#good2#good3#good4#good5#good6#good7#good8#good9#good10
     2  good1#good2#good3#good4#good5#good6#good7#good8#good9#good10
     3  good11#good12#good13#good14#good15#good16#good17#good18#good19#good20
     4  good21#good22#good23#good24#good25#good26#good27#good28#good29#good30

sky92@sky92:~$ awk -v FS="#" '{print $1}'  /tmp/awktest2.txt
good1
good1
good11
good21
sky92@sky92:~$ awk -v FS="#" '{print NR,$1}'  /tmp/awktest2.txt
1 good1
2 good1
3 good11
4 good21
sky92@sky92:~$ awk -v FS="#" '{print NR,$1,$(NF-1)}'  /tmp/awktest2.txt
1 good1 good9
2 good1 good9
3 good11 good19
4 good21 good29
 
```

### 多文件处理

```shell
sky92@sky92:~$ awk '{print NR,$0}'  /tmp/awktest.txt  /tmp/awktest2.txt
1 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30
5 good1#good2#good3#good4#good5#good6#good7#good8#good9#good10
6 good1#good2#good3#good4#good5#good6#good7#good8#good9#good10
7 good11#good12#good13#good14#good15#good16#good17#good18#good19#good20
8 good21#good22#good23#good24#good25#good26#good27#good28#good29#good30

sky92@sky92:~$ awk '{print FNR,$0}'  /tmp/awktest.txt  /tmp/awktest2.txt
1 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30
1 good1#good2#good3#good4#good5#good6#good7#good8#good9#good10
2 good1#good2#good3#good4#good5#good6#good7#good8#good9#good10
3 good11#good12#good13#good14#good15#good16#good17#good18#good19#good20
4 good21#good22#good23#good24#good25#good26#good27#good28#good29#good30
 

```

### 自定义换行符

```shell

sky92@sky92:~$ awk '{print NR,$0}'  /tmp/awktest.txt
1 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk -v RS=' ' '{print NR,$0}'  /tmp/awktest.txt
1 good1
2 good2
3 good3
4 good4
5 good5
6 good6
7 good7
8 good8
9 good9
10 good10
good1
11 good2
12 good3
13 good4
14 good5
15 good6
16 good7
17 good8
18 good9
19 good10
good11
20 good12
21 good13
22 good14
23 good15
24 good16
25 good17
26 good18
27 good19
28 good20
good21
29 good22
30 good23
31 good24
32 good25
33 good26
34 good27
35 good28
36 good29
37 good30

#指定行结尾续加内容  去除了换行符
sky92@sky92:~$ awk -v ORS='---' '{print NR,$0}'  /tmp/awktest.txt
1 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10---2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10---3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20---4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30---

```

### 其他

```shell
sky92@sky92:~$ awk '{print FILENAME,NR,$0}'  /tmp/awktest.txt
/tmp/awktest.txt 1 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
/tmp/awktest.txt 2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
/tmp/awktest.txt 3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
/tmp/awktest.txt 4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'BEGIN{print "START:"}{print $0}'  /tmp/awktest.txt
START:
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'BEGIN{print "START:"}{print ARGV[0],$0}'  /tmp/awktest.txt
START:
awk good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
awk good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
awk good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
awk good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'BEGIN{print "START:"}{print ARGV[1],$0}'  /tmp/awktest.txt
START:
/tmp/awktest.txt good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
/tmp/awktest.txt good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
/tmp/awktest.txt good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
/tmp/awktest.txt good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'BEGIN{print "START:"}{print ARGV[2],$0}'  /tmp/awktest.txt
START:
 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'BEGIN{print "START:"}{print ARGV[0],ARGV[1],ARGV[2]}'  /tmp/awktest.txt   /tmp/awktest2.txt
START:
awk /tmp/awktest.txt /tmp/awktest2.txt
awk /tmp/awktest.txt /tmp/awktest2.txt
awk /tmp/awktest.txt /tmp/awktest2.txt
awk /tmp/awktest.txt /tmp/awktest2.txt
awk /tmp/awktest.txt /tmp/awktest2.txt
awk /tmp/awktest.txt /tmp/awktest2.txt
awk /tmp/awktest.txt /tmp/awktest2.txt
awk /tmp/awktest.txt /tmp/awktest2.txt

#自定义局部变量
sky92@sky92:~$ awk -v myname="sky" 'BEGIN{print "MY NAME IS : ",myname}'
MY NAME IS :  sky

#自定义全局shell变量 并被awk引用
sky92@sky92:~$ myname="sky92"
sky92@sky92:~$ awk -v awk_name=$myname 'BEGIN{print "MY NAME IS : ",awk_name}'
MY NAME IS :  sky92

```

### 格式化输出

```shell
sky92@sky92:~$ awk '{print $0}' /tmp/awktest.txt
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

#printf不做格式指定的时候是 无换行输出
sky92@sky92:~$ awk '{printf $0}' /tmp/awktest.txt
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10good1 good2 good3 good4 good5 good6 good7 good8 good9 good10good11 good12 good13 good14 good15 good16 good17 good18 good19 good20good
 
```

printf 配合format 做格式化输出 

| 符号   | 解释                                 |
| ------ | ------------------------------------ |
| %c     | 显示字符ASCII码                      |
| %d，%i | 十进制数                             |
| %e，%E | 科学计数法                           |
| %f     | 显示浮点数                           |
| %g，%G | 科学计数法格式或浮点数的格式显示数值 |
| %s     | 显示字符串                           |
| %u     | 无符号整数                           |
| %%     | 显示%自身                            |
| -      | 左对齐  默认是右对齐                 |
| +      | 显示数值符号printf “%+d”             |

```shell

sky92@sky92:~$ awk '{printf $0}' /tmp/awktest.txt
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10good1 good2 good3 good4 good5 good6 good7 good8 good9 good10good11 good12 good13 good14 good15 good16 good17 good18 good19 good20good

sky92@sky92:~$ awk '{printf "%s\n",$0}' /tmp/awktest.txt
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ printf "%s\n" a b c d e f
a
b
c
d
e
f

sky92@sky92:~$ printf "%s--\n" a b c d e f
a--
b--
c--
d--
e--
f--

sky92@sky92:~$ awk 'BEGIN{printf "%d\n",1,3,2,4}'
1
sky92@sky92:~$ awk 'BEGIN{printf "%d%d\n",1,3,2,4}'
13
sky92@sky92:~$ awk 'BEGIN{printf "%d%d%d\n",1,3,2,4}'
132
sky92@sky92:~$ awk 'BEGIN{printf "%d-%d\n%d-%d\n",1,3,2,4}'
1-3
2-4

sky92@sky92:~$ awk '{printf "first: %s - second: %s \n",$1,$2}' /tmp/awktest.txt
first: good1 - second: good2
first: good1 - second: good2
first: good11 - second: good12
first: good21 - second: good22

sky92@sky92:~$ awk 'BEGIN{printf "%-10s %-10s\n","first:","second:"}{printf "%-10s %-10s \n",$1,$2}' /tmp/awktest.txt
first:     second:
good1      good2
good1      good2
good11     good12
good21     good22







```

### 模式

```shell

sky92@sky92:~$ awk '{print $0}' /tmp/awktest.txt
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
good21 good22 good23 good24 good25 good26 good27 good28 good29 good30

sky92@sky92:~$ awk 'BEGIN{print "开始操作"}{print $0}END{print "结束操作"}' /tmp/awktest.txt
开始操作
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
good21 good22 good23 good24 good25 good26 good27 good28 good29 good30
结束操作

sky92@sky92:~$ awk 'NR<4{print NR,$0}' /tmp/awktest.txt
1 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20

sky92@sky92:~$ awk 'NR<=4{print NR,$0}' /tmp/awktest.txt
1 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
2 good1 good2 good3 good4 good5 good6 good7 good8 good9 good10
3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30


sky92@sky92:~$ awk 'NR>=3{print NR,$0}' /tmp/awktest.txt
3 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20
4 good21 good22 good23 good24 good25 good26 good27 good28 good29 good30




```



```shell
#awk '/正则表达/动作' 文件
#awk '/正则表达1/,/正则表达2/ {动作}' 文件

sky92@sky92:~$ cat -n /tmp/test2.txt
     1  I like linux
     2  I have a NAS
     3  I have a PC.
     4  I have learn linux.
     5  the website is https://space.bilibili.com/5548363
     6  #note
     7  gooooooood
     
sky92@sky92:~$ awk '/^I/{print $0}' /tmp/test2.txt
I like linux
I have a NAS
I have a PC.
I have learn linux.
  
```



## 实战

```shell
sky92@sky92:~$ ifconfig docker0
docker0   Link encap:以太网  硬件地址 02:42:4f:17:cd:6e
          inet 地址:172.17.0.1  广播:172.17.255.255  掩码:255.255.0.0
          inet6 地址: fe80::42:4fff:fe17:cd6e/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  跃点数:1
          接收数据包:19563516 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:17424630 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:0
          接收字节:12109989039 (12.1 GB)  发送字节:4126438365 (4.1 GB)

sky92@sky92:~$ ifconfig docker0 | awk 'NR==2{print $2}'
地址:172.17.0.1
 
```

```shell
sky92@sky92:~$ cat -n /tmp/historytest.txt
     1   2279  awk -v FS="#" '{print NR,$1,$(NF-1)}'  /tmp/awktest2.txt
     2   2280  cat -n /tmp/awktest2.txt
     3   2281  awk -v FS="#" '{print NR,$0}'  /tmp/awktest.txt  /tmp/awktest2.txt
     4   2282  awk '{print NR,$0}'  /tmp/awktest.txt  /tmp/awktest2.txt
     5   2283  awk '{print NR,$0}'  /tmp/awktest.txt  /tmp/awktest2.txt
     6   2284  awk '{print FNR,$0}'  /tmp/awktest.txt  /tmp/awktest2.txt
     7   2285  awk '{print NR,$0}'  /tmp/awktest.txt
     8   2286  awk -v RS=' ' '{print NR,$0}'  /tmp/awktest.txt
     9   2287  awk '{print NR,$0}'  /tmp/awktest.txt
    10   2288  awk -v ORS='---' '{print NR,$0}'  /tmp/awktest.txt
    11   2289  awk '{print FILENAME,NR,$0}'  /tmp/awktest.txt
    12   2290  awk 'BEGIN{print start:}{print,$0}'  /tmp/awktest.txt
    13   2291  awk 'BEGIN{print start:}{print $0}'  /tmp/awktest.txt
    14   2292  awk 'BEGIN{print 'start:'}{print $0}'  /tmp/awktest.txt
    15   2293  awk 'BEGIN{print "start:"}{print $0}'  /tmp/awktest.txt
    16   2294  awk 'BEGIN{print "START:"}{print $0}'  /tmp/awktest.txt
    17   2295  awk 'BEGIN{print "START:"}{print ARGV[0],$0}'  /tmp/awktest.txt
    18   2296  awk 'BEGIN{print "START:"}{print ARGV[1],$0}'  /tmp/awktest.txt
    19   2297  awk 'BEGIN{print "START:"}{print ARGV[2],$0}'  /tmp/awktest.txt
    20   2298  awk 'BEGIN{print "START:"}{print ARGV[3],$0}'  /tmp/awktest.txt
    21   2299  awk 'BEGIN{print "START:"}{print ARGV[0],ARGV[1],ARGV[2]}'  /tmp/awktest.txt   /tmp/awktest2.txt
    22   2300  awk -v myname="sky" 'BEGIN{print "MY NAME IS : ",myname}'
    23   2301  myname="sky92"
    24   2302  awk -v awk_name=$myname 'BEGIN{print "MY NAME IS : ",awk_name}'
    25   2303  awk '{print $0}' /tmp/awktest.txt
    26   2304  awk '{printf $0}' /tmp/awktest.txt
    27   2305  awk '{printf "%s"$0}' /tmp/awktest.txt
    28   2306  awk '{printf "%s",$0}' /tmp/awktest.txt
    29   2307  awk '{printf "%s\n",$0}' /tmp/awktest.txt
    30   2308  printf "%s\n" a b c d e
    31   2309  printf "%s\n" a b c d ef
    32   2310  printf "%s\n" a b c d e f
    33   2311  printf "%s--\n" a b c d e f
    34   2312  awk '{printf "%s",$0}' /tmp/awktest.txt
    35   2313  awk '{printf "%s\n",$0}' /tmp/awktest.txt
    36   2314  awk '{printf "%d\n",1,3,2,4}'
    37   2315  awk 'BEGIN{printf "%d\n",1,3,2,4}'
    38   2316  awk 'BEGIN{printf "%d%d\n",1,3,2,4}'
    39   2317  awk 'BEGIN{printf "%d%d%d\n",1,3,2,4}'
    40   2318  awk 'BEGIN{printf "%d-%d \n %d-%d \n",1,3,2,4}'
    41   2319  awk 'BEGIN{printf "%d-%d \n%d-%d \n",1,3,2,4}'
    42   2320  awk 'BEGIN{printf "%d-%d\n%d-%d\n",1,3,2,4}'
    43   2321  awk '{printf "first: %s  - segund: %s  -  third: %s",$1,$2,$3}' /tmp/awktest.txt
    44   2322  awk '{printf "first: %s  - secend: %s  -  third: %s",$1,$2,$3}' /tmp/awktest.txt
    45   2323  awk '{printf "first: %s  - second: %s  -  third: %s",$1,$2,$3}' /tmp/awktest.txt
    46   2324  awk '{printf "first: %s \nsecond: %s  \nthird: %s",$1,$2,$3}' /tmp/awktest.txt
    47   2325* awk '{printf "first: %s \nsecond: %s  \nthird: %s",$1$}' /tmp/awktest.txt
    48   2326  awk '{printf "first: %s \nsecond: %s  \nthird: %s",$1,$2,$3}' /tmp/awktest.txt
    49   2327  awk '{printf "first: %s \nsecond: %s \n ",$1,$2,$3}' /tmp/awktest.txt
    50   2328  awk '{printf "first: %s \nsecond: %s \n ",$1,$2}' /tmp/awktest.txt
    51   2329  awk '{printf "first: %s \nsecond: %s \n",$1,$2}' /tmp/awktest.txt
    52   2330  awk '{printf "first: %s second: %s \n",$1,$2}' /tmp/awktest.txt
    53   2331  awk '{printf "first: %s - second: %s \n",$1,$2}' /tmp/awktest.txt
    54   2332  awk '{printf "first: %-25s - second: %s \n",$1,$2}' /tmp/awktest.txt
    55   2333  awk '{printf "first: %-10s - second: %s \n",$1,$2}' /tmp/awktest.txt
    56   2334  awk '{printf "%-10s - second: %s \n",$1,$2}' /tmp/awktest.txt
    57   2335  awk '{printf "%-10s %s \n",$1,$2}' /tmp/awktest.txt
    58   2336  awk 'BEGIN{first:}{printf "%-10s %s \n",$1,$2}' /tmp/awktest.txt
    59   2337  awk 'BEGIN{print "first:"}{printf "%-10s %s \n",$1,$2}' /tmp/awktest.txt
    60   2338  awk 'BEGIN{print "first:","second:"}{printf "%-10s %s \n",$1,$2}' /tmp/awktest.txt
    61   2339  awk 'BEGIN{printf "%-10s","first:","second:"}{printf "%-10s %s \n",$1,$2}' /tmp/awktest.txt
    62   2340  awk 'BEGIN{printf "%-10s %-10s","first:","second:"}{printf "%-10s %s \n",$1,$2}' /tmp/awktest.txt
    63   2341  awk 'BEGIN{printf "%-10s %-10s\n","first:","second:"}{printf "%-10s %s \n",$1,$2}' /tmp/awktest.txt
    64   2342  awk 'BEGIN{printf "%-10s %-10s\n","first:","second:"}{printf "%-10s %-10s \n",$1,$2}' /tmp/awktest.txt
    65   2343  awk '{print $0}' /tmp/awktest,
    66   2344  awk '{print $0}' /tmp/awktest.txt
    67   2345  awk 'BEGIN{"开始操作"}{print $0}' /tmp/awktest.txt
    68   2346  awk 'BEGIN{print "开始操作"}{print $0}' /tmp/awktest.txt
    69   2347  awk 'BEGIN{print "开始操作"}{print $0}END{printf "结束s操作"}' /tmp/awktest.txt
    70   2348  awk 'BEGIN{print "开始操作"}{print $0}END{printf "结束操作"}' /tmp/awktest.txt
    71   2349  awk 'BEGIN{print "开始操作"}{print $0}END{print "结束操作"}' /tmp/awktest.txt
    72   2350  awk 'NR<4{print NR,$0}' /tmp/awktest.txt
    73   2351  awk 'NR<=4{print NR,$0}' /tmp/awktest.txt
    74   2352  awk 'NR>=3{print NR,$0}' /tmp/awktest.txt
    75   2353  cat -n /tmp/test
    76   2354  cat -n /tmp/test.txt
    77   2355  cat -n /tmp/test2.txt
    78   2356  awk '/^I/{printf $0}' /tmp/test2.txt
    79   2357  awk -F ":" '/^I/{printf $0}' /tmp/test2.txt
    80   2358  awk -F ":" '/^I/{print $0}' /tmp/test2.txt
    81   2359  awk'/^I/{print $0}' /tmp/test2.txt
    82   2360  awk '/^I/{print $0}' /tmp/test2.txt
    83   2361  awk -F=" " '/^I/{print $0}' /tmp/test2.txt
    84   2362  cat -n /tmp/pwd.txt
    85   2363  cat -n /tmp/path.txt
    86   2364  awk -F=" " '/^I/{print $0}' /tmp/path.txt
    87   2365  awk -F=":" '/^I/{print $0}' /tmp/path.txt
    88   2366  awk -F=":" '/^I/{print $0}' /tmp/path.txt
    89   2367  awk -F=":" '/^bin/{print $0}' /tmp/path.txt
    90   2368  awk -F=":" '/^\//{print $0}' /tmp/path.txt
    91   2369  awk'/^I/{print $0}' /tmp/test2.txt
    92   2370  grep 'nologin' /tmp/path.txt
    93   2371  awk '{print $1}' access.log |sort -n | uniq | wc-l
    94   2372  awk '{print $1}' /tmp/path.txt |sort -n | uniq | wc-l
    95   2373  awk '{print $1}' /tmp/path.txt |sort -n | uniq | wc -l
    96   2374  awk '{print $1}' /tmp/path.txt |sort -n | uniq
    97   2375  awk '{print $1}' /tmp/pwd.txt |sort -n | uniq
    98   2376  awk '{print $1}' /tmp/pwd.txt |sort -n | uniq | wc -l
    99   2377  awk '{print $1}' /tmp/pwd.txt |sort -n | uniq -c
   100   2378  history | tail -100 > /tmp/historytest.txt



#去重后总计数量
sky92@sky92:~$ awk '{print $2}' /tmp/historytest.txt |sort -n | uniq | wc -l
7

#在数据开头 显示重复数量 
sky92@sky92:~$ awk '{print $2}' /tmp/historytest.txt |sort -n | uniq -c
     85 awk
      2 awk'/^I/{print
      6 cat
      1 grep
      1 history
      1 myname="sky92"
      4 printf
#在数据开头 显示重复数量 并再次排序      
sky92@sky92:~$ awk '{print $2}' /tmp/historytest.txt |sort -n | uniq -c |sort -nr
     85 awk
      6 cat
      4 printf
      2 awk'/^I/{print
      1 myname="sky92"
      1 history
      1 grep
    
```





