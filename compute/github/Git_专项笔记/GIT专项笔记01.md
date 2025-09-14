# GIT手册

[TOC]

## 第一课 GIT安装

```shell
sudo apt-get install git
```

或下载源代码 编译安装

### GIT使用初始化


```shell
#注册GIT
git config --global user.name  "用户名"
git config --global user.email "邮箱"
```


```shell
#查看看配置 
git config --list
```



```txt
GIT工作流
	1-在工作目录中添加修改文件
	2-将需要进行版本管理的文件爱你放入暂存区
	3-将暂存区的文件交道GIT仓库

GIT管理的文件有三种状态
	已修改 	modified
	已暂存		staged
	已提交		committed
```

### 常规操作

```shell
#建立仓库 
git init
#文件下产生 .git文件

#添加文件 
git add readme_file.md

git add * 	#添加工作目录里的所有文件
git add .	#效果同上

#提交暂存区文件到仓库
git commit -m "add a readme file"

#添加远程仓库
git remote add origin https://git_remote_address.git

#传到远程仓库
git push origin
```


```shell
#将工作目录的文件爱你放到GIT仓库需要两步
git add 文件名
git commit -m "你干了啥"
```



## 第二课

```shell
#查看GIT状态 
git status
#创建LICENSE  将MIT协议写入
#同文件夹下新增且没有放入git里的文件 会在git status 时提示
```



```shell
#返回方法： 
#释放指定暂存区内的文件
git reset HEAD filename.txt
	
#释放最后一次进入暂存区的文件
git reset HEAD 

#覆盖文件： 
#把暂存区的LICENSE文件覆盖到工作区改过的LICENSE文件
git checkout -- LICENSE  
	
#工作区LICENSE文件被修改后  使用git status查看  
#会出现暂存区和工作区两个LICENSE文件
```


```shell
#查看历史提交记录 
git log
```

## 第三课

```shell
#reset 和 checkout

#在仓库汇中 指向代码的上一个快照 将暂存区恢复为该快照
git reset HEAD~	
	
#再上一个快照
git reset HEAD~~ 
	
#前N个快照   波浪号个数
git reset HEAD~N 

```



```shell
#reset命令的选项
git reset --mixed HEAD~   	#（默认指令）
	
#移动HEAD的指向 将上一个快照
#将HEAD移动后指向的快照回滚到暂存区

git reset --soft HEAD~ 

#移动HEAD的指向 将上一个快照  相当于撤销上一次提交

git reset --hard HEAD~

#移动HEAD的指向 将上一个快照  相当于撤销上一次提交
#将HEAD移动后指向的快照回滚到暂存区域
#将暂存区的文件还原到工作目录
--soft 	#移动HEAD的指向
--mixed	#将快照回滚到暂存区
--hard	#将暂存区还原到工作目录
```


```shell
#回滚指定快照  回滚个别文件
#指定快照ID	
git reset  文件SHA1哈希值（版本快照ID号）
```

?	

## 第四课

```shell
#创建工作文件夹 MyProject2 

#创建项目跟踪	
git init  

#创建README.md文件
touch README.md

#提交入暂存区	
git add 文件 	

#提交项目	
git commit -m "注释"

# 查看当前暂存区文件
git ls-files
```

  	

```shell
#修改工作区内的文件内容
#比较工作区文件和暂存区文件	
git diff 

	index 旧文件ID  新文件ID    旧文件权限新文件权限
	---	为暂存区旧文件
	+++	为工作区新文件

	带+号为新文件特有的

	J K 上下键  
	F向下翻页   D向下翻半页 U 向上翻半页

	g 跳转到最后一行  
	G 跳转到第一行

	3  g   跳转到第三行

	/ 从上往下搜索
	？从下往上搜索
	n 下一个匹配字

	h 进入帮助文档
	q 退出

#比较仓库中不同的历史快照
git diff 快照1的ID  快照2的ID
```


```shell
#比较工作区中和仓库中的快照
git diff 快照ID    	
git diff HEAD
```

```shell
#比较暂存区中和仓库中的快照
git diff --cached 	  	#（比较仓库最新快照）
git diff --cached  ID	#（比较仓库指定快照）
```

?	

## 第五课

```shell
#两种情况：
#1 版本刚提交到仓库，发现漏掉两个文件没有添加
#2 版本提交发现版本说明写的不够全面 无法显示修改意义

#修改最后一次提交 
#执行带 --amend 选项的 commit 提交命令
#GIT就会更正最近一次提交
git commit --amend  --m "说明"

#进入新界面修改提交说明
#按下 i 键  开始添加     backspace删除文本
#ESC推出编辑模式   
#shift加两下Z  保存推出
#:q! 不保存退出

#将快照中的文件恢复到工作区
git checkout -- README.md

#删除工作区和暂存区某个文件 （取消跟踪 下次提交不进入仓库） 
git rm 文件名		

#消除某个文件在暂存区内的更改
git checkout 文件名
git restore 文件名

#消除当前目录下所有的在暂存区内的更改
git checkout .
git restore .

#将指针恢复到上个快照 撤销上一次提交
git checkout HEAD~

#强制删除 暂存区 和 工作目录的文件
git rm -f 文件名

#仅仅删除暂存区文件  保留工作区文件
git rm --cached 文件名

#显示未跟踪的文件
git clean -dn
#删除所有未跟踪文件
git clean -df

#重命名文件
git mv 旧名 新名

#结合三步 
ren/mv 	旧名 新名
git rm 	旧名
git add 新名
```

## 第六课


	#创建分支
	git branch 分支名称


```shell
#查看一下 
git log --decorate --oneline 
	--decorate #显示所有指向快照的引用
	--oneline #简介显示	
	--graph #图像化显示
	--all #显示所有分支

git log --decorate --oneline --graph --all

#切换分支
git checkout 分支名称
```

## 第七课


```shell
#实际开发分支 
#	master		发布分支
#	hotfix		BUG修复分支
#	release		功能集合编译
#	develop		开发测试分支
#	feature		功能开发区

#合并分支
git merge 分支名称

#当两个分支都有同名且都修改过的文件  发生 冲突

#修改文件名 
git mv 旧名 新名	

#创建并还原到分支
git checkout -b 分支名称
git switch -c 分支名称

#删除分支 
git branch -d 分支名称
```


远程
```shell
#查看远程仓库
git remote -v
#修改远程仓库的本地别名
git remote rename oldname newname 
#移除与远程仓库的连接
git remote rm old_reposity_name 
#新增仓库   origin为默认 可以改为其他名称
git remote add origin git_remote_address
git remote add github git@github.com:User/RepoName.git
git remote add gitee git@gitee.com:User/RepoName.git
 
```

远程推送


```shell
#推送到 origin 别名连接的远程仓库 中 的 master 分支  
# -u 参数   把本地的master分支内容推送的远程新的master分支，还会把本地的master分支和远程的master分支关联起来 可以简化命令
git push -u origin master
```

 

## 第八课

```sh
#匿名分支 
#用于实验

#reset 默认只将指定的文件恢复到暂存区 
#reset 无法在使用了 --soft 和 --hard 后再指定文件

#checkout 同时覆盖暂存区和工作区

#reset 命令家移动HEAD指针（--soft） 
#-> 覆盖暂存区（--mixed，默认）
#-> 覆盖工作区（--hard）

#checkout 切换指针 然后 覆盖暂存区和工作区

#相对于reset --hard 来说 checkout 命令更加安全，
#checkout在切换分之前会检查当前工作状态
#如果不是“clean”的话 GIT不会允许执行操作 
#而  reset --hard 则覆盖所有数据
```



## 第九课 消除和还原

消除未跟踪的变更

```shell
######消除未跟踪的变更  消除未跟踪文件的变更#####

#消除某个未跟踪文件的更改
git checkout 文件名
git restore 文件名
Updated 1 paths from the index

#消除当前目录下所有未跟踪文件的更改
git checkout .
git restore .
Updated 2 paths from the index

#显示未跟踪的文件
git clean -dn
#删除所有未跟踪文件
git clean -df

```

消除已跟踪的变更 

```shell
######消除已跟踪的的变更  消除已在暂存区文件的变更#####

#文件加入跟踪
git add test.txt
warning: LF will be replaced by CRLF in second.txt.
The file will have its original line endings in your working directory

#试图还原文件 但没有成功
git checkout test.txt
Updated 0 paths from the index

#查看状态
git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   test.txt
#回溯操作
git reset  test.txt
git restore --staged test.txt
Unstaged changes after reset:
M       test.txt

#还原文件成功
git checkout test.txt
Updated 1 paths from the index
 
```

### 提交回退

```shell
#产生文件
echo 'test' > test.txt

#跟踪文件
git add test.txt
warning: LF will be replaced by CRLF in unrequired.txt.
The file will have its original line endings in your working directory

#查看跟踪文件
git ls-files
.gitignore
test.txt

#提交
git commit -m 'test file added'
[master db9cca2] test file added
 1 file changed, 1 insertion(+)
 create mode 100644 test.txt

#查看日志
git log
commit db9cca2fd80f8489cd9d6000a74f4e6dee7beecd (HEAD -> master)
Author: sky92archangel <sky92@DESKTOP-P8SB3R8>
Date:   Sat Mar 18 16:20:41 2023 +0800

    test file added

commit a19c8053b448e48b4ea2638ec58d3677d6e3b3bd
Author: sky92archangel <sky92@DESKTOP-P8SB3R8>
Date:   Sat Mar 18 16:09:57 2023 +0800

    my-first-commit

#回退一步 软重置 删除最近一次提交 并将其中的文件变更移出暂存区
git reset --soft HEAD~1
#回退一步 硬重置 删除最近一次提交 且硬盘文件实时变更 
git reset --hard HEAD~1

#再次查看日志
git log
commit a19c8053b448e48b4ea2638ec58d3677d6e3b3bd (HEAD -> master)
Author: sky92archangel <sky92@DESKTOP-P8SB3R8>
Date:   Sat Mar 18 16:09:57 2023 +0800

    my-first-commit
 
 
```

### 删除分支

```shell
#删除多个分支
git branch -D second-branch third-branch
git branch -d second-branch third-branch
 
```

### 临时离群分支

```shell
#查看日志
git log
commit db9cca2fd80f8489cd9d6000a74f4e6dee7beecd (HEAD -> master)
Author: sky92archangel <sky92@DESKTOP-P8SB3R8>
Date:   Sat Mar 18 16:20:41 2023 +0800

    test file added

commit ed8a19a0b240541e79600659ed25e5b7830c1441
Author: sky92archangel <sky92@DESKTOP-P8SB3R8>
Date:   Sat Mar 18 16:09:57 2023 +0800

    my-first-commit
    
#以某个提交状态创建离群分支
git checkout ed8a19a0b240541e79600659ed25e5b7830c1441 

Note: switching to 'ed8a19a0b240541e79600659ed25e5b7830c1441'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by switching back to a branch.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -c with the switch command. Example:

  git switch -c <new-branch-name>

Or undo this operation with:

  git switch -

Turn off this advice by setting config variable advice.detachedHead to false

HEAD is now at ed8a19a reset test
 
#修改文件 并提交
echo 'gogog' > unrequired.txt && git add . && git commit -m 'change test file'

warning: LF will be replaced by CRLF in unrequired.txt.
The file will have its original line endings in your working directory
[detached HEAD 2f880cd] change test file
 1 file changed, 1 insertion(+), 1 deletion(-)

#回到一般分支
git switch master
Warning: you are leaving 1 commit behind, not connected to
any of your branches:

  2f880cd change test file

If you want to keep it by creating a new branch, this may be a good time
to do so with:

 git branch <new-branch-name> 2f880cd

Switched to branch 'master'
  
#建立离群分支
git branch detached-head 2f880cd    
#转到分支
git switch detached-head
Switched to branch 'detached-head'

#查看该分支
git log
commit 2f880cd85ab35ff4c66c01e8dc843722980d0a2b (HEAD -> detached-head)
Author: sky92archangel <sky92@DESKTOP-P8SB3R8>
Date:   Sat Mar 18 16:48:37 2023 +0800

    change test file

#回到一般分支
git switch master
Switched to branch 'master'

#合并
git merge detached-head
  
    

```



## 第十课 大文件问题

### 情况分析

1. 本地add之后发现误操作将大文件加入暂存
2. 已经提交至本地仓库，但没有同步至远程仓库
3. 已经同步至远程仓库
4. 非本人操作，但远程库已经存在大文件

### 对策

### 情况123

```shell
########1 本地add之后发现误操作将大文件加入暂存 ########
#将文件从暂存区中删除
git rm --cached video.mp4


########2 已经提交至本地仓库，但没有同步至远程仓库    ########
#reset到上一版本
git reset HEAD^	
#然后回收垃圾
git gc


########3 已经同步至远程仓库  ########
#首先垃圾回收
git gc 	
#然后使用扩展的git命令filter-repo  下载地址：https://github.com/newren/git-filter-repo
#删除所有提交中的这个文件， 这个文件的commit和文件本体都会消失
git filter-repo --path=glob video.mp4 --invert-paths --force 
#然后再一次垃圾回收
git gc --aggressive
#重添加git远程库引用
git remote add origin git@XXXXX.github.com:sskk/demo.git
#强制所有推送
git push --all --force
#推送所有tag
git push --tags --force

```

###  复杂情况4

```shell
########4 非本人操作，但远程库已经存在大文件 且不一定在当前分支 ########
#首先垃圾回收
git gc
#从pack中寻找大文件
#git verify-pack -v .git.objects/pack/*.idx 输出所有objectid 大小 等
#grep blob过滤出blob对象
#sort -k 3 -n 结果以第三个字段排序
#cut -f 1 -d " "  按照空格分离字段
#去除尾部tail -10
#为寻找top10大的blob对象 显示为    ID  文件名  两列
git rev-list --objects --all || grep -f <(git verify-pack -v .git.objects/pack/*.idx | grep blob | sort -k 3 -n | cut -f 1 -d " " | tail -10)
###获得体积前10大的文件简单命令，需要自定义该操作
git largefiles -t 10
#然后使用扩展的git命令filter-repo  下载地址：https://github.com/newren/git-filter-repo
#删除所有提交中的这个文件， 这个文件的commit和文件本体都会消失
git filter-repo --path=glob video.mp4 --invert-paths --force
#然后再一次垃圾回收
git gc --aggressive
#重添加git远程库引用
git remote add origin git@XXXXX.github.com:sskk/demo.git
#强制所有推送
git push --all --force
#推送所有tag
git push --tags --force

#如果要查看获得的文件大小需要cat-file ID
git cat-file -s 2018138e1385c1e8c1e384c1e8331e87
```

若已经做了多测commit，但是远程不接受大文件

```shell

# 搜索所有提交中包含的 .tar.gz 文件
git log --pretty=format: --name-only | sort -u | grep "\.tar\.gz$"
#  从所有历史提交中删除 tar.gz 文件
# 推荐使用 git filter-branch（无需额外安装工具，兼容性好）：
git filter-branch --force --index-filter  "git rm --cached --ignore-unmatch file_to_delete.tar.gz"   --prune-empty --tag-name-filter cat -- --all

# 清理引用日志
git reflog expire --expire=now --all

# 彻底清理未引用的对象
git gc --prune=now --aggressive

# 推送到 gitee（替换为你的远程名，如 origin）
git push gitee --force

# 同样推送到 gitlab
git push gitlab --force

rm 要删除的文件.tar.gz  # 物理删除本地文件
```



若要保留大文件

```shell
# 安装 Git LFS（如未安装）
git lfs install

# 跟踪所有 tar.gz 文件
git lfs track "*.tar.gz"

# 提交跟踪规则
git add .gitattributes
git commit -m "Add LFS tracking for tar.gz files"

# 重新添加并提交大文件（此时会被 LFS 管理）
git add 要保留的文件.tar.gz
git commit -m "Re-add tar.gz file with LFS"

# 推送（LFS 会单独传输大文件）
git push gitee
git push gitlab
```



## 第十一课 引入外部项目

### 1.git子项目

一般从github上下载的大型项目多数会引用其他项目的git库作为子模块
那么想要把子模块递归的拉到本地就需要采用git submodule功能

```shell
# 直接源码编译
git submodule add git@gitee.com:roberchen/spdlog.git
git submodule init
git submodule update --init --recursive
# 移除子模块
git submodule deinit -f path/to/submodule
git rm-f path/to/submodulerm -rf .git/modules/path/to/submodule
```

### 2.外部项目引入

```cmake
#在编译时下载项目并引入到主项目中
include(ExternalProject)
ExternalProject_Add(SPDLOG
    PREFIX	 			${SPDLOG_ROOT}
    GIT REPOSITORY	 	${SPDLOG_GIT_URL}
    GIT_TAG    			${SPDLOG_GIT_TAG}
    CONFIGUR_COMMAND 	$SPDLOG_CONFIGURE}
   	BUILD_COMMAND	 	${SPDLOG_MAKE}   
    INSTALL_COMMAND		${SPDLOG_INSTALL}
 )
```



### 3.直接从线上拉下来编译

```cmake
cmake_minimum required(VERSION 3.16)
project(gtest_test)
set(CMAK_CXX_STANDARD 17)
include(FetchContent)
FetchContent Declare(
    googletest
    GIT REPOSITORY https://github.com/google/googletest.git
    GIT TAG 1.14.0
)
FetchContent_MakeAvailable(googletest)
add exedtable(gtest_test gtest_test.cpp)
target_link_libraries(gtest_test gtest_main)
```







## 附录 疑难问题



#### 问题描述

使用git的时候发现一直提示**HTTP/2 stream 1 was not closed cleanly before end of the underlying stream。**通过排查发现，是git默认使用的通信协议出现了问题，可以通过将默认通信协议修改为http/1.1来解决该问题。

#### 解决方法

```shell
git config --global http.version HTTP/1.1
```

