# Docker基础

[TOC]

## 安装

```shell
#删除旧版本
sky92@sky92:~$ sudo apt-get remove docker docker-engine docker.io containerd runc 
#依赖
sky92@sky92:~$ sudo apt-get install apt-transport-https ca-certificates curl gnupg-agent software-properties-common
#添加 Docker 的官方 GPG 密钥：
sky92@sky92:~$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
#添加软件源
sky92@sky92:~$ sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sky92@sky92:~$ sudo apt-get update
#安装
sky92@sky92:~$ sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose
#测试
sky92@sky92:~$ sudo docker run hello-world

#安装compose
sudo curl -L "https://github.com/docker/compose/releases/download/1.25.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
docker-compose --version

```

### 权限

```shell
#让当前账户也能使用sudo权限运行docker
#创建docker组
sky92@sky92:~$ sudo groupadd docker
#将当前用户添加到该docker组
sky92@sky92:~$ sudo usermod -aG docker $USER
#重新登录
su - $USER
#测试是否安装成功
docker run hello-world
```

### 卸载

```SHELL
#卸载
sky92@sky92:~$ sudo apt-get purge docker-ce docker-ce-cli containerd.io docker docker.io
sky92@sky92:~$ sudo rm -rf /var/lib/docker
sky92@sky92:~$ sudo apt autoremove
```

### 国内镜像

```shell
#修改配置文件
sky92@sky92:~$ sudo vim /etc/docker/daemon.json

#添加国内镜像
{
  "registry-mirrors": [
    "https://hub-mirror.c.163.com",
    "https://mirror.ccs.tencentyun.com",
    "https://docker.mirrors.ustc.edu.cn"
  ]
}

#更新镜像缓存
sky92@sky92:~$ sudo systemctl daemon-reload
sky92@sky92:~$ sudo systemctl restart docker
```

##  安装2025更新

在 Ubuntu 22.04 上安装 Docker 时，如果遇到“没有可用的软件包 docker-ce”的错误，可能是由于软件源配置不正确或网络问题导致无法访问 Docker 的官方仓库。以下是解决此问题的详细步骤：

### **解决步骤**

#### **1. 更新系统包**

确保系统包是最新的：

bash复制

```bash
sudo apt update
sudo apt upgrade -y
```

#### **2. 安装必要的依赖包**

安装一些必要的包，这些包用于允许 `apt` 通过 HTTPS 使用仓库：

bash复制

```bash
sudo apt install -y apt-transport-https ca-certificates curl gnupg lsb-release
```

#### **3. 添加 Docker 的官方 GPG 密钥**

运行以下命令来添加 Docker 的官方 GPG 密钥：

bash复制

```bash
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
```

#### **4. 添加 Docker 的 APT 仓库**

将 Docker 的 APT 仓库添加到系统中：

bash复制

```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

#### **5. 更新 APT 包索引**

添加完软件源后，更新包索引：

bash复制

```bash
sudo apt update
```

#### **6. 安装 Docker**

现在可以尝试再次安装 Docker：

bash复制

```bash
sudo apt install -y docker-ce docker-ce-cli containerd.io
```

### **替代方案**

如果上述步骤仍然无法解决问题，可以尝试以下替代方案：

#### **1. 使用阿里云镜像源**

阿里云提供了稳定的 Docker 镜像源。可以使用以下命令配置阿里云的 Docker 源：

bash复制

```bash
curl -fsSL http://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
echo "deb [arch=$(dpkg --print-architecture)] http://mirrors.aliyun.com/docker-ce/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt update
sudo apt install -y docker-ce docker-ce-cli containerd.io
```

#### **2. 使用 Docker 官方一键安装脚本**

Docker 官方提供了一键安装脚本，适用于多种操作系统：

bash复制

```bash
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
```

需要注意的是，这种方式安装的可能是体验版而非稳定版，建议不用于生产环境。

### **验证安装**

安装完成后，可以通过以下命令验证 Docker 是否安装成功：

bash复制

```bash
sudo docker run hello-world
```

如果看到“Hello from Docker!”的输出，说明 Docker 已成功安装。

通过上述步骤和替代方案，你应该能够顺利解决“没有可用的软件包 docker-ce”的问题。



## 建立和运行

### 镜像版本区别

| 版本     | 说明                                                         | 示例                                                         |
| -------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| alpine   | Alpine Linux 操作系统，它是一个独立发行版本，相比较 Debian 操作系统来说 Alpine，更加轻巧 https://alpinelinux.org/ | docker pull node:alpine3.14                                  |
| squeeze  | Debian 6                                                     |                                                              |
| wheezy   | `Debian 7`                                                   |                                                              |
| jessie   | `Debian 8`，更旧的稳定（oldoldstable）版，马上就淘汰了 2015 https://wiki.debian.org/DebianJessie | `docker pull node:10.22.0-jessie`                            |
| stretch  | `Debian 9`，旧的稳定（oldstable）版，现有长期支持 2017，比较老，目前除了 LTS 其他版本已经不再提供技术支持了，所以我们非必要情况下还是不要选择它比较好 https://wiki.debian.org/DebianStretch | docker pull node:lts-stretch                                 |
| buster   | Debian 10，当前的稳定（stable）版 2019，比较新，支持比较全面，受广大Debian爱好者的好评！像 PHP、Python 之类的语言、应用都会使用这个版本的 Debian 搭建 Docker 基础镜像 https://wiki.debian.org/DebianBuster | docker pull node:lts-buster                                  |
| bullseye | `Debian 11`，即将上位的稳定（stable）版 2021 https://wiki.debian.org/DebianBullseye | `docker pull node:lts-bullseye`                              |
| xxx-slim | 一般都基于 Debian 和 glibc，删除了许多非必需的软件包，优化了体积 | `docker pull node:stretch-slim` `docker pull node:buster-slim` |



### 基本操作

容器操作

```shell
#查看运行中的容器
sky92@sky92:~$ docker ps 
#查看所有容器
sky92@sky92:~$ docker ps -a
#开始运行容器 运行已存在容器
sky92@sky92:~$ docker start 容器ID
sky92@sky92:~$ docker start 容器名称
#停止容器
sky92@sky92:~$ docker stop 容器ID
sky92@sky92:~$ docker stop 容器名称
```

镜像操作

```shell
#查看镜像
sky92@sky92:~$ docker images
#删除镜像
sky92@sky92:~$ docker rmi  镜像ID
sky92@sky92:~$ docker rmi  镜像名称
#强制删除
sky92@sky92:~$ docker rmi  镜像ID --force
```

假设已经安装完成docker并配置最快的源

拉取docker镜像，建议使用一般镜像，若对环境要求高容量有限时可选定制瘦镜像
``` shell
docker pull python:latest
```

运行容器 复杂 
``` shell
docker run -itd -p 8888:8888 -v ~/myapp:/usr/src/myapp -w /bin/bash --name python-env python:latest

# _/myapp  为宿主机目录，用来放python脚本 
#/usr/src/myapp 为python 容器内的目录
#-w 选项 为`-w, --workdir=""`， 指定容器的工作目录
#-p为指定对外端口 ，前一个为宿主机端口，后一个是容器端口 这里的8888预留给jupyter
#--name 为容器指定一个名称 python-env
# python:latest 为使用的镜像名称 
```

进入运行中的容器

```shell
docker exec -it python-env /bin/bash
```
在容器内命令行
pip安装所需的包

``` shell
pip install -i https://pypi.tuna.tsinghua.com.edu.cn jupyterlab 
```


完成后配置
```shell
jupyter notebook --generate-config
jupyter notebook password #（会输入两次密码，用来验证）
```
配置后运行
```shell
jupyter-lab --ip=0.0.0.0 --port=8888 --allow-root
```


在浏览器输入网址访问 


### docker网络通讯
创建一个docker网络
```shell
docker network create test-net
```
重新运行容器 并同时指定网络

```shell
docker run -d --name redis --network test-net --network-alias redisNet redis:latest
# --name redis 指定容器名称
# --network test-net 指定容器所在网络
# --network-alias redisNet 指定容器在网络内的别名
```

若我们要将上述的python环境和redis放在一个网络内，操作如下
```shell
docker run -itd -p 8888:8888 -v ~/myapp:/usr/src/myapp -w /bin/bash --name python-env --network test-net --network-alias pythonNet python:latest

#-i 表示允许我们对容器进行操作 
#-t 表示在新容器内指定一个为终端 
#-d 表示容器在后台执行
# _/myapp  为宿主机目录，用来放python脚本 
#/usr/src/myapp 为python 容器内的目录
#-w 选项 为`-w, --workdir=""`， 指定容器的工作目录
#-p为指定对外端口 ，前一个为宿主机端口，后一个是容器端口 这里的8888预留给jupyter
#--name 为容器指定一个名称 python-env
# python:latest 为使用的镜像名称 
#--network test-net 指定容器所在网络
#--network-alias pythonNet 指定容器在网络内的别名
```


注意：如果现有容器没有添加至网络，但又不想失去容器内的部分配置，可以docker commit把旧容器打包为镜像，重新开辟为新容器；

### 三种方式

docker容器的建立通过三种方式：docker命令行，dockerfile，docker-compose

下面以pytorch的安装为例；

```shell
#首先从dockerhub上拉镜像
sky92@sky92:~$ docker pull torch_env_sky:v1
```

#### 直接命令行形式：

```shell
#建立容器命令  
docker run -itd \
--name pytorch_jupyter \
--gpus all \ 
-p 18888:8888 \
-v D:/WORKSPACE/DOC/DL/pytorch:/workspace  \
--privileged=true \
torch_env_sky:v1

#-i 表示允许我们对容器进行操作 
#-t 表示在新容器内指定一个为终端 
#-d 表示容器在后台执行
#--name 指定容器名称
#--gpus 指定gpu的直通，深度学习必备
#-p 将本地端口和容器内端口绑定   这里的容器内端口为8888是容器内jupyter的默认端口；  本地端口:容器内端口
#-v 挂载 ，将容器内目录绑到本地目录，当然要保证镜像内有该目录 ；  本地目录:容器内目录
#--privileged 权限
#torch_env_sky:v1  这是我自己的镜像名称，也可以是dockerhub上的其他镜像
 
#查看容器
sky92@sky92:~$ docker ps -a
CONTAINER ID   IMAGE                                          COMMAND   CREATED      STATUS                  PORTS     NAMES
7a5fd57627a5   torch_env_sky:v1                               "bash"    9 days ago   Exited (0) 7 days ago             pytorch_jupyter 

#进入容器命令行
sky92@sky92:~$ docker exec -it pytorch_jupyter bash
root@7a5fd57627a5:/# 
#命令行内可以对容器进行部分修改  下载配置其他需要的服务等 所做操作都会被保存 所作只要容器不删除 就不会消失
#若需要保存当前容器作为新的镜像，则参考下述导入导出一节

```

#### Dockerfile形式

dockerfile 建立python环境的docker镜像 

```dockerfile
#一个dockerfile
#拉取一个已经存在的基础镜像
FROM  python:3.9

#维护者
MAINTAINER sky	

#设置镜像自带环境变量 该变量在容器运行时依然有效 后续可以通过$NAME 等来访问 和bash一个规则  类似有个ARG其定义只在镜像构建时有效
ENV NAME="python-env" 
ENV PYTHON_VERSION="3.9" 

#需要复制进入镜像作为镜像一部分的文件 可以不指定 在后期运行时也可以挂载  部分时候使用 COPY代替ADD  不过ADD具有自解压功能
ADD /data/repo		

#进入操作的目录  相当于bash中的cd命令
WORKDIR /app  

#构建镜像时需要执行的操作  即为bash指令  这里我们在python环境内安装一个jupyter
RUN echo 'start install jupyter'
RUN apt-get update && apt-get install vim
RUN pip3 install jupyterlab 
 
#将容器内的/data文件夹挂载为本地匿名卷 可以不指定 在后期运行时也可以挂载 毕竟不同主机的工程代码目录不同  类似命令行内模式-v 
#宿主机会在/var/lib/docker/volume下创建一个挂载目录路径 容器删除后，宿主机/var/lib/docker/volume下挂载目录不会删除
VOLUME /data/project
#也可以填入多个挂载
VOLUME ["/data1","/data2"]

#开放镜像对外端口 可以不指定 在后期运行时也可以挂载  相当于命令行内模式-p
EXPOSE 8888 						

#运行容器时需要执行的操作 用于启动程序 CMD ["参数1","参数2"] 如查看系统版本 CMD["cat","/etc/os-release"] 
CMD ["/bin/bash"]
CMD jupyter-lab --allow-root
#多参数运行容器  ENTRYPOINT 启用后【 docker run 镜像 --allow-root 】后面的命令会作为参数传入容器和jupyter进行组合运行
ENTRYPOINT ["curl","-s","http://ipinfo.io/ip"]
ENTRYPOINT ["jupyter-lab" ]

```

运行上述dockerfile文件

```shell
#-t 指定镜像命和版本号 建立镜像 此时
sky92@sky92:~$ docker build -t python_env:v1 . 

#运行
sky92@sky92:~$ docker run -itd -p 18888:8888 --name test-python python_env:v1

sky92@sky92:~$ docker ps -a
CONTAINER ID   IMAGE                                          COMMAND     CREATED         STATUS                     PORTS     NAMES
d40df495db46   62d9bfc73383                                   "python3"   5 seconds ago   Exited (0) 4 seconds ago             test-python

#可见容器运行情况
```

  

#### docker-compose

Docker Compose 是 Docker 容器进行编排的工具，定义和运行多容器的应用，可以一条命令启动多个容器；如果没有 docker-compose，那么每次启动的时候，你需要敲各个容器的启动参数，环境变量，容器命名，指定不同容器的链接参数等等一系列的操作，相当繁琐。

案例

docker-compose.yaml 文件

```yaml
version: "3.3"
services:
  mysql:
    image: mysql:5.7.28
    restart: always
    environment:
      - MYSQL_ROOT_PASSWORD=admin888
      - MYSQL_DATABASE=wordpress
  wordpress:
    image: wordpress:latest
    restart: always
    depends_on:
      - mysql
    environment:
      - WORDPRESS_DB_HOST=mysql:3306
      - WORDPRESS_DB_PASSWORD=admin888
      - WORDPRESS_DB_USER=root
      - WORDPRESS_DB_NAME=wordpress
    ports:
      - "8080:80"
    working_dir: /var/www/html
    volumes:
      - ./html:/var/www/html
```

| 属性        | 说明                                                        |
| ----------- | ----------------------------------------------------------- |
| version     | 当前文件格式版本，不同版本配置属性不同                      |
| services    | 容器列表                                                    |
| image       | 容器使用的镜像                                              |
| environment | 容器环境变量                                                |
| restart     | DOCKER 进程重起时重起容器 no:不重起，always:保持重起        |
| depends_on  | 依赖的容器                                                  |
| ports       | 宿主机和容器之间的端口映射关系                              |
| working_dir | 工作目录即 wordpress 项目目录                               |
| volumes     | 容器和宿主机的卷映射关系，将.html 映射到容器的/var/www/html |

现在访问 `127.0.0.1:8080` 将会看到 wordpress 界面了

##### 网络

如果 `docker-compose.yaml` 存在于 **composefile** 目录中，系统会自动创建 composefile_default 网络，所有容器会加入这个网络，容器间也可以使用容器名进行连接通信。

所以上例中的 wordpress 容器中的 PHP 代码可以使用 mysql 来连接 mysql 容器

每次执行`docker-compose up` 后容器的 IP 地址会发生改变

##### 常用命令

查看容器

```shell
#查看运行中的容器
sky92@sky92:~$ docker ps
sky92@sky92:~$ docker-compose ps
#查看所有容器
sky92@sky92:~$ docker ps -a
```

重起项目的服务

```shell
sky92@sky92:~$ docker-compose restart
```

重起指定容器

```shell
sky92@sky92:~$ docker-compose restart mysql
```

起动编排的容器

```shell
sky92@sky92:~$ docker-compose up -d
```

关闭容器

```shell
sky92@sky92:~$ docker-compose down
```

删除容器

```shell
sky92@sky92:~$ docker-compose rm mysql
```

 

### 注：

docker依靠镜像为基础启动容器，容器相当于镜像加料运行的程序，必须有一个前台命令才能保持活性，否则立马关闭，这个问题在nginx的部署上很明显；如下为nginx的dockerfile正确写法

```dockerfile
CMD ["nginx","-g","daemon off;"]
```

 

## 导入导出

如果需要导出镜像
（1）使用 docker export 命令根据容器 ID 将镜像导出成一个文件。

```shell
 sky92@sky92:~$ docker export 容器ID > torch_env_sky.tar
```
（2）上面命令执行后，可以看到文件已经保存到当前的 docker 终端目录下。

如果需要导入镜像
（1）使用 docker import 命令则可将这个镜像文件导入进来。

``` shell
 sky92@sky92:~$ docker import - torch_env_sky < torch_env_sky.tar
```
（2）执行 docker images 查看镜像是否已经导入。 

 

## 实例



```shell
#docker安装网页绘图工具
sky92@sky92:~$ docker run --rm -itd --name excalidraw -p 5000:80 excalidraw/excalidraw:latest

#安装第三方nginx分支版本openresty
docker run -d --name=openresty -p 8886:80  -v /home/sky92/docker_data/nginx/conf/nginx.conf:/etc/nginx/nginx.conf  -v /home/sky92/docker_data/nginx/conr_data/nginx/log:/var/log/nginx -v /home/sky92/docker_data/nginx/html:/usr/share/nginx/html --privileged=true --restart=always openresty/openresty


#resilio-sync 互联网P2P同步工具
docker create \
--name=resilio_sync \
-e PUID=1000 \
-e PGID=1000 \
-e TZ=Asia/Shanghai \
-e UMASK_SET=022 \
-p 8888:8888 \
-p 55555:55555 \
-v /home/sky92/docker_data/resilio_sync/config:/config \
-v /home/sky92/docker_data/resilio_sync/downloads:/downloads \
-v /home/sky92/docker_data/resilio_sync/sync:/sync \
--restart unless-stopped \
linuxserver/resilio-sync
 
```

















