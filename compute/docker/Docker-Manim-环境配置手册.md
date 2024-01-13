

# Manim的Docker开发环境搭建

记录时间 2022-02



#### 零、准备工作

由于manim在物理机上的配置需要ffmpeg python环境等 较为繁琐，且被有操作系统洁癖的用户视作巨大危机；Manim早期提供了Docker配置环境的方式，当前源码的文件中也有dockerfile，可是目前原作者GitHub上Docker配置条目被删，但社区版提供的方法依然可行，本说明无需使用dockerfile；

1. 首先确保已经下载并安装了docker程序 ，docker的安装配置不赘述；
2. 从github上下载manim源码到本地 ，这里假设为 D盘根目录    D:/manim   ； 
3. 打开bash或powershell命令行；下列内容在Linux和Window系统中差距并不大 ；

>  manim原作者源码  https://github.com/3b1b/manim  ；
>
> manim社区源码：https://github.com/ManimCommunity/manim
>
> 社区版Docker文档：https://docs.manim.community/en/stable/installation/docker.html

> docker快速入门 ：https://docker.easydoc.net/doc/81170005  ；



#### 一、首先是查找dockerhub是否有manim库

```powershell
PS C:\Users\Administrator> docker search manim

NAME                         DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
eulertour/manim              Development image for manim, an animation en…   23
manimcommunity/manim         Docker images for the community-maintained v…   2
jasonkwan/manim                                                              2
manimaul/tsdb                                                                0
manimdsl/manimdsl-api                                                        0
kayvan/manimal-tomcat        Prepared manimal Tomcat image with memcached…   0
manimdsl/manimdsl-frontend                                                   0
manimanimani/frontend                                                        0
garykim/manim                                                                0
manimaccse/frontend                                                          0
manimaran/appmonitoring                                                      0
smithea3/manim               Test build of manim.                            0                    [OK]
manimdsl/manimdslcompiler                                                    0
manimaul/xio                 Images for building, running and testing [xi…   0
manimediaserver/nginx        An Nginx container, brought to you by LinuxS…   0
manimaul/mxmariner.com                                                       0
alex76treeheir/manim         image of manim, forked from 3b1b, correct so…   0
manisl339/manimaven                                                          0
tonycrane/manim_tex          A docker image with texlive-full for manim      0
nikeee/manim-flipdot                                                         0
manisl339/manimw                                                             0
manimaul/android-sdk         Container image with the Android SDK and NDK.   0
manimaransys/nginx                                                           0
tlcoding/manimce             manimce image using the latest python           0
manimaransys/elasticsearch                                                   0
 
```

上述我们注意到两个docker镜像   **eulertour/manim**    和   **manimcommunity/manim** ；

这里的    **eulertour/manim**   为早期版本  ， 多年未更新，若你想体验原始的manim可以使用该镜像；

这里的    **manimcommunity/manim**   为社区版本，一直更新中，收藏和下载较多，故我们选用这个镜像；



#### 二、拉取镜像

````powershell
PS C:\Users\Administrator> docker pull manimcommunity/manim
````

此时我们获得了社区版制作的镜像  manimcommunity/manim  之后我们要根据该镜像创建容器；



#### 三、将本地工程目录挂载到镜像中去，并且启动镜像

由于我们搭建的是开发环境，肯定不希望随着docker容器的关闭或删改导致开发的代码消失，这里我们使用volume方式挂载我们的代码；

1. 这里指定容器名称为  manim-dev  ；
2. 挂载本地目录   D:/manim   到  容器内部的 /app 目录，manim文件夹中包含GitHub上下载的的manim代码；
3. 指定向外通讯端口 8080:8080   若本机8080端口被占 ，仅仅需要修改冒号前的8080为其他端口；

注：冒号前是主机端口，后是docker容器端口，此处manim环境暂时不需要网络服务，所以该项只是摆设；

```powershell
PS C:\Users\Administrator> docker run -p 8080:8080 --name=manim-dev -v D:/manim:/app -d manimcommunity/manim
```

若执行后打印显示sha256码，那么容器创建成功并运行了；



#### 四、进入容器的命令行开始操作

```powershell
PS C:\Users\Administrator> docker exec -it manim-test bash
```

此时已经进入了运行的容器，开始配置容器内的环境，我们使用注意我们将manim挂载到了容器的/app目录下

```bash
cd /app
#输入manim测试代码
python3 -m manim example_scenes.py SquareToCircle -pl
```

请注意：若git上下载的是社区版   example_scenes  要替换为  test_scenes

#若成功， 此时会在代码根目录的media文件夹下产生视频文件（社区版）
#若失败， 通常由于缺少部分python库  使用python -m pip install ... 来安装就行  

若直接成功我们可以直接使用该环境做开发，本说明第五步无需进行；

若失败，但经过配置成功运行，则需要进行本说明的第五步；



#### 五、重新将当前的容器打包成为新的镜像

由于容器内修改内容重启后会消失，那么我们需要将OK的环境保存为镜像后，再次启动为新容器即可开始开发；

1. 保证需要打包的容器正在运行；
2. 指定作者author，指定提交信息 manim-env-info；
3. containerID代表需要打包为镜像的容器ID，可以通过docker ps  命令查询容器ID  ；
4. 指定最终镜像的名称和版本标签   manim-community-env:v1.1

```powershell
PS C:\Users\Administrator> docker commit -a "author" -m "manim-env-info" containerID  manim-community-env:v1.1
```

由此我们获得了OK的开发环境镜像  manim-community-env:v1.1

由此我们可以再次重复本说明第三、第四步，完成容器的建立；







