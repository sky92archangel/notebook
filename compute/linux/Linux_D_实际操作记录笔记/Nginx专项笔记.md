# Nginx 专项笔记

[TOC]

sky92@sky92:~$

## 安装

安装问题可参看 OpenResty 的安装，其为多模块的nginx

如果需要简易安装nginx ，执行如下命令

```shell
sky92@sky92:~$ sudo apt-get install nginx-full
#检查安装状态
sky92@sky92:~$ nginx -v
nginx version: nginx/1.18.0 (Ubuntu)
#查看运行状态
sky92@sky92:~$ sudo systemctl status nginx.service
● nginx.service - A high performance web server and a reverse proxy server
     Loaded: loaded (/lib/systemd/system/nginx.service; enabled; vendor preset: enabled)
     Active: active (running) since Tue 2024-04-09 20:15:53 CST; 12s ago
       Docs: man:nginx(8)
    Process: 2544 ExecStartPre=/usr/sbin/nginx -t -q -g daemon on; master_process on; (code=exited, status=0/SUCCESS)
    Process: 2545 ExecStart=/usr/sbin/nginx -g daemon on; master_process on; (code=exited, status=0/SUCCESS)
   Main PID: 2546 (nginx)
      Tasks: 5 (limit: 4566)
     Memory: 4.9M
        CPU: 22ms
     CGroup: /system.slice/nginx.service
             ├─2546 "nginx: master process /usr/sbin/nginx -g daemon on; master_process on;"
             ├─2547 "nginx: worker process" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" ""
             ├─2548 "nginx: worker process" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" ""
             ├─2549 "nginx: worker process" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" ""
             └─2550 "nginx: worker process" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" "" ""

4月 09 20:15:53 sky92-virtual-machine systemd[1]: Starting A high performance web server and a reverse proxy server...
4月 09 20:15:53 sky92-virtual-machine systemd[1]: Started A high performance web server and a reverse proxy server.

#检查配置文件
sky92@sky92:~$ sudo nginx -t -c /etc/nginx/nginx.conf
nginx: the configuration file /etc/nginx/nginx.conf syntax is ok
nginx: configuration file /etc/nginx/nginx.conf test is successful

```

### 默认的安装的异常处理 

```shell
#尝试停止使用端口 80 的进程： 
sky92@sky92:~$ sudo fuser -k 80/tcp
sky92@sky92:~$ sudo systemctl restart nginx
```



## 配置文件

```shell
#配置文件位置 
sky92@sky92:~$ ls /etc/nginx/
conf.d          koi-win            nginx.conf       sites-enabled
fastcgi.conf    mime.types         proxy_params     snippets
fastcgi_params  modules-available  scgi_params      uwsgi_params
koi-utf         modules-enabled    sites-available  win-utf
#/etc/nginx/nginx.conf就是配置文件

#建议讲原始配置文件做个副本，我们要重写配置文件
sky92@sky92:~$ sudo cp /etc/nginx/nginx.conf /etc/nginx/nginx.conf.bak
sky92@sky92:~$ sudo rm /etc/nginx/nginx.conf
sky92@sky92:~$ sudo touch /etc/nginx/nginx.conf
#此时配置文件改动后需要重加载
sky92@sky92:~$ sudo nginx -s reload 
sky92@sky92:~$ sudo nginx -t
nginx: the configuration file /etc/nginx/nginx.conf syntax is ok
nginx: configuration file /etc/nginx/nginx.conf test is successful

```





























