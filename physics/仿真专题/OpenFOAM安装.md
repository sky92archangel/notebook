# [OpenFOAM](https://openfoam.org/)

 

## 安装



```shell
sudo sh -c "wget -O - http://dl.openfoam.org/gpg.key | apt-key add -"
sudo add-apt-repository http://dl.openfoam.org/ubuntu
sudo apt-get update 
sudo apt-get -y install openfoam10

#多版本切换要求
sudo nano ~/.bashrc
#添加如下内容  这里根据你现有的安装版本决定
alias of10='source /opt/openfoam10/etc/bashrc'
alias of11='source /opt/openfoam11/etc/bashrc'

#使用时命令行直接输入 of10 即可进入OpenFoam10的环境
of10

```

 