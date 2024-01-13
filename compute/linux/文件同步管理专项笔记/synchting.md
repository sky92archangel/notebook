

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

