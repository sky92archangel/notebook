# 环境搭建

[TOC]

sky92@sky92:~/workspace/gsl_course/code01$  

## LINUX环境

环境部署在远程linux服务器，由本地vscode链接

注意：GSL只能运行于linux环境，windows方面的开发请安装虚拟机或者采用WSL；

## GSL安装

### 下载源码

```shell
sky92@sky92:~$ wget -P /tmp  https://mirror.ibcp.fr/pub/gnu/gsl/gsl-latest.tar.gz
sky92@sky92:~$ cd /tmp
sky92@sky92:/tmp$ tar -zxvf gsl-latest.tar.gz
sky92@sky92:/tmp$ cd /tmp/gsl-latest/gls-2.8/
```

### 编译安装

```shell
#创建安装目录
sky92@sky92:~$ mkdir -p /home/sky92/workspace/clib/GSL 
#预检指定目录
sky92@sky92:/tmp/gsl-latest/gls-2.8$ ./configure --prefix=/home/sky92/workspace/clib/GSL 
#编译和安装
sky92@sky92:/tmp/gsl-latest/gls-2.8$ make
sky92@sky92:/tmp/gsl-latest/gls-2.8$ make install
```

 

## 测试源码

源码目录

```shell
/home/sky92/workspace/gsl_course/code01/
```

makefile

```makefile
GCC=gcc 

LIB=/home/sky92/workspace/clib/GSL/lib # gsl lib path
INCLUDE=/home/sky92/workspace/clib/GSL/include # gsl include path

FLAGS=-lgsl -lgslcblas -lm # gsl flags

gslstudy: gslstudy.c
	$(GCC) -o gslstudy gslstudy.c -I$(INCLUDE) -L$(LIB) $(FLAGS)

clean:
	rm -f gslstudy

```

gslstudy.c

```C
#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>

int main(void)
{
    double x = 5.0;
    double y = gsl_sf_bessel_J0(x);
    printf("J0(%g) = %.18e\n", x, y);
    return 0;
}
```

## vscode远程调试

安装vscode，安装扩展remote-ssh，注意远程调试时 code runner扩展无效

## 运行

编译

```shell
sky92@sky92:~$ cd /home/sky92/workspace/gsl_course/code01/
sky92@sky92:~/workspace/gsl_course/code01$ make
#产生一个可执行文件
sky92@sky92:~/workspace/gsl_course/code01$ ./gslstudy
```

报错提示，若出现该错误需要添加环境变量

```SHELL
./gslstudy: error while loading shared libraries: libgsl.so.28: cannot open shared object file: No such file or directory
```

添加环境变量

```SHELL
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/sky92/workspace/clib/GSL/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/sky92/workspace/clib/GSL/bin
```

