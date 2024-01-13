

# conda





### 创建

```shell
# OCC 7.5.1
conda create --name=env_name python=3.7
source activate env_name 
#几个常用库
pip install scipy numpy  jupyter
#pyside环境
activate env_name
pip install pyside2 -i https://pypi.douban.com/simple/
#pyqt环境
activate env_name
pip install PyQt5-tools -i https://pypi.douban.com/simple

```



```json
#linux 为 ~/.pip/pip.conf
#windows为 %HOMEPATH%\pip   一般是 c:\users\admin\pip\pip.ini
# coding: GBK
[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
[install]
trusted-host = https://pypi.tuna.tsinghua.edu.cn
#清华大学：https://pypi.tuna.tsinghua.edu.cn/simple
#阿里云：http://mirrors.aliyun.com/pypi/simple/
#豆瓣：http://pypi.douban.com/simple/
```



jupyter

```shell
#安装
pip install  jupyter
#配置文件生成
jupyter notebook --generate-config
#打开C:\Users\admin\.jupyter\jupyter_notebook_config.py
c.NotebookApp.notebook_dir='C:\default_folder'

#代码自动补全扩展
pip install jupyter_contrib_nbextensions
jupyter contrib nbextensions install --user
pip install jupyter_nbextensions_configurator
#重新启动Jupyter notebook
jupyter notebook --no-browser --port=8898 --ip=127.0.0.1

#设置密码
jupyter notebook password
#C:\Users\admin\.jupyter\jupyter_server_config.json

```





### 镜像

conda 国内源

```json
#打开.condarc文件：
channels:
  - https://mirrors.ustc.edu.cn/anaconda/pkgs/main/
  - https://mirrors.ustc.edu.cn/anaconda/pkgs/free/
  - https://mirrors.ustc.edu.cn/anaconda/cloud/conda-forge/
ssl_verify: true 
```



### 代理

```
#代理pip:
Clash for Windows -> Settings -> System Proxy -> [v] Specify Protocol
```



```json
#打开.condarc (C:\Users\xxxx\.condarc)并添加
proxy_servers:
  http: http://127.0.0.1:7890
  https: http://127.0.0.1:7890
#其中127.0.0.1:7890是实际的代理端口
```

 