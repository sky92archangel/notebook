# Xubuntu初始化配置

[TOC]

## 国内源更换

```shell
#备份原地址数据
sky92@sky92:~$ cp /etc/apt/source.list /etc/apt/source.list.backup
#修改/etc/apt/source.list
sky92@sky92:~$ sudo nano /etc/apt/source.list
```

2022版本代号为jammy

```bash
#deb cdrom:[Xubuntu 22.04.1 LTS _Jammy Jellyfish_ - Release amd64 (20220809.1)]/ jammy main multiverse restricted universe 

#阿里源
deb http://mirrors.aliyun.com/ubuntu/ jammy main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ jammy-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ jammy-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ jammy-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ jammy-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ jammy-backports main restricted universe multiverse


#网易源
deb http://mirrors.163.com/ubuntu/ jammy main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ jammy-security main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ jammy-updates main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ jammy-proposed main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ jammy-backports main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy-security main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy-updates main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy-proposed main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ jammy-backports main restricted universe multiverse

#清华源
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse
deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse


##中科大源
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse

```

然后更新

```shell
sky92@sky92:~$ sudo apt-get update
```

 

## 远程SHH

ssh链接，内网无法远程连接的主要因素就是这个：

```shell
sky92@sky92:~$ sudo apt-get install openssh-server
```

## 文件同步syncthing

默认端口 8384

```shell
#下载的syncthing文件syncthing-linux-amd64-v1.19.2.tar.gz
sky92@sky92:~$ tar -zxvf syncthing-linux-amd64-v1.19.2.tar.gz
sky92@sky92:~$ cd syncthing-linux-amd64-v1.19.2  
```

方法1

```shell
#最好使用无浏览器模式 --no-browser
#IP归为0.0.0.0 可以在局域网内其他浏览器中访问这个WEBUI
sky92@sky92:~/syncthing-linux-amd64-v1.19.2$ ./syncthing --no-browser -gui-address="0.0.0.0:8384" --home="/home/USERNAME/SYNC_DIR"
#随后就是各机器互相ID认证 开始使用
```

方法2

```shell
#安装supervisorctl
#配置syncthing.conf如下
[program:syncthing]
command=/home/USERNAME/programs/syncthing/syncthing --no-browser -gui-address="0.0.0.0:8384" --home="/home/USERNAME/.config/syncthing"
directory=/home/USERNAME/programs/syncthing
user=USERNAME
autostart=true
autorestart=true
environment = STNORESTART="1",HOME="/home/USERNAME"
#su->supervisorctl relaod (重启supervisord)->supervisorctl 查看状态
```

## VNC远程可视化

```shell
#安装
sky92@sky92:~$ sudo apt-get install tigervnc-standalone-server
#设定密码
sky92@sky92:~$ vncpasswd
#浏览
sky92@sky92:~$ ls ~/.vnc/
#编辑
sky92@sky92:~$ sudo nano ~/.vnc/xstartup
```

简易版本xstartup

```bash
#!/bin/sh
unset SESSION_MANAGER
unset DBUS_SESSION_BUS_ADDRESS
exec startxfce4
```

启动

```shell
sky92@sky92:~$ vncserver -geometry 1920x1080 -localhost no -alwaysshared
#默认端口 5901或者5902
```

 

## samba共享

```shell
#安装
sky92@sky92:~$ sudo apt install samba samba-common

#共享的文件夹最好是777权限的
sky92@sky92:~$ sudo chmod 777 /share/ -R

#添加samba认证用户  必须是系统内已经存在的账号 
sky92@sky92:~$ sudo smbpasswd -a sky92

#备份samba配置文件
sky92@sky92:~$ sudo cp /etc/samba/smb.conf /etc/samba/smb.conf.bak

#修改配置文件
sky92@sky92:~$ sudo nano /etc/samba/smb.conf 

#在smb.conf文件最后添加如下配置
[share-folder]
comment = share-folder
browseable = yes
path = /share_dir
guest ok = yes
writable = yes
valid users = sky92
  
#重启  
sky92@sky92:~$ sudo service smbd restart
```







































