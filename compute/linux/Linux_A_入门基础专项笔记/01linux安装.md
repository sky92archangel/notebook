# Linux安装

[TOC]



## 安装界面


install or upgrade    尽量安装驱动  

install system with    尽量保证基本图形界面 

rescue installed     拯救已经安装的操作系统    会出现回复环境

boot from  local drive   本地硬盘启动    跳过光盘引导

memory test   内存测试 在生产环境下  测试硬件




注： 安装程序也是linux操作系统




是否校验光盘     可忽略  节省时间


CentOS    社区版红帽   诞生于社区的企业操作系统

选择磁盘驱动  
	basic storeage    普通PC或者实验机
	speciallzed   storage      存储 服务器  专用存储盘柜   以太网



是否格式化所有数据       新盘  选是



设置主机名 


时区   UTC  格林威治时间


设置ROOT用户密码

磁盘分区

	所有空间   全盘自动创建分区
	
	修改
	
	使用空闲

大多分区比较危险  建议创建自制分区

硬盘   sda 第一块硬盘   sdb第二块硬盘    sda1 第一块盘的主分区第一块   
	software RAID 软RAID      LVM  逻辑卷  将所有硬盘统一整理

	swap  交换分区  超过4G 就设4G  小于4G 设内存两倍    服务器最多16G
	
	force to  be  primary partition   强制分到主分区
	
	Encrypt 目录加密   安全装置   影响性能   但 能从物理上保密

配置引导 若有多块 需要选择   默认MBR

	可对引导程序加密

发行版本开源软件的安装选择  默认最小化

	可选基础服务器  网络服务器  虚拟化服务等 
	
	初学者可选择 桌面环境desktop

检查依赖性  可自动解决依赖关系


开始安装


重启进入grub界面  引导操作系统



启动  版权信息

	创建普通用户
	
	配置时间  synchronize  网络时间同步  服务器专用  NTP 网络时间服务
	
	Kdump  当死机时  可把当前内存数据备份出来  


​	
重启   





































