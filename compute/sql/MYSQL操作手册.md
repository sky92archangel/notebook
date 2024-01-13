#  MYSQL 手册

[TOC]



## 第一课 MYSQL 的安装配置

### 安装

```shell
yum install -y mysql-server-*
apt-get install mysql-server mysql-client
```

### 启动

```shell
service mysql start
service mysqld start

service mysql restart
service mysqld restart

#使用 systemctl 也可以
```

### 配置

```shell
#root密码初始化
mysqladmin -u root password 'root-new-password'
```

登录root

```shell
mysql -u root -p 
chkconfig mysqld on
```

配置文件

```shell
/etc/my.cnf
```

创建的数据库保存位置（可从配置文件内配置）

```shell
/var/lib/mysql
```

默认日志文静位置

```shell
/var/log/my.log
```

默认端口 3306

```shell
#查找端口是否监听	
netstat -tupln | grep 3306
```



## 第二课 基本操作

### mysql连接方法

```shell
mysql -h localhost -u root -p

mysql -h 数据库所在地址 -u 登录用户 -p

#默认是连接到本地
```

### 进入sql后

```mysql
-- 操作语句通常大写  也可以小写

-- 查看数据库版本   大多语句用分号结尾

	SELECT VERSION();	

-- 获取当前时间

	SELECT CURRENT_DATE ;

-- 两者合并

	SELECT VERSION(),CURRENT_DATE ;

-- 基本数学计算

	SELECT 4+4；
	SELECT 4*4；

-- 查看当前数据库

	SHOW DATABASES ;
```

### 库操作

```mysql
-- 创建数据库

	CREATE DATABASE 数据库名;

-- 删除数据库

	DROP DATABASE 数据库名 ;

-- 切换当前使用的数据库

	USE 数据库名 ;

-- 创建数据库名称确定后无法重命名
```

 

## 第三课 SQL语言

###  基本操作


```mysql
-- 进入数据库 显示数据库信息

	SELECT * FROM 数据库名  ;

-- SQL 语句分类

-- 	DDL-data delinttion language 定义语言 对数据库本身修改

		CREATE 		创建
		ALTER		修改
		DROP		删除
	
-- 	DML-data manipulation language  数据库维护语言 对数据库内容

		SELECT 		选取
		INSERT		插入
		UPDATE		更新
		DELETE		删除

-- 	DCL-data control language 控制语言 操控权限

		GRANT		给予一个用户的各种权限
		REVOKE		移除一个用户的各种权限
```


```mysql
-- 	TCL-transaction control
	
		COMMIT		保存数据操作
		SACEPOINT	为仿版标记一个事务点
		ROLLBACK	从最后一次commit恢复到最后状态
```

### 创建


```mysql
-- 数据库管理

-- 	创建数据库

		CREATE DATABASE 数据库名 ;

-- 	删除数据库
	
		DROP DATABASE 数据库名 ；

-- 	创建完成后 无法重命名数据库
```


```mysql
-- 数据类型

	integer(size) int(size) smalint(size) tinyint(size) 储存整数
	
	decimal(size,d) numeric(size,d) 储存浮点

	char(size)	固定长度字符串

	varchar（size）	可变长度字符串

	date（yyyymmdd）存日期
```


```mysql
-- 创建表格

	CREATE TABLE 表名称

	(

	列名称1 数据类型，
	列名称2 数据类型，
	列名称3 数据类型，
	...

	)

	CREATE TABLE lc_course

	(

	id int，
	course_name varchar(50)，
	course_length int(10)，
	teacher varchar(50),
	category varchar(50)

	)

	SHOW TABLES ;
```


```mysql
-- 查看表结构

	DESCRIBE 表名字 ;
	DESC 表名字 ;   (简写)

-- 删除表格

	DROP TABLE 表名字 ;
```


```mysql
-- 修改表

-- 	重命名表

		ALTER TABLE 原名 RENAME 新名;

-- 	向表中添加一列 ； 

		ALTER TABLE 表名 ADD 新列 ;
		ALTER TABLE lc_course ADD link varchar(100) ;

-- 	删除表中一列

		ALTER TABLE 表名 DROP 要删除的列名 ;
		ALTER TABLE lc_course DROP link varchar(100) ;

-- 	修改列的数据类型
		
		ALTER TABLE 表名 MODIFY 列名 数据类型 ;
		ALTER TABLE lc_course MODIFY teacher varchar(100);

-- 	重命名一个列

		ALTER TABLE 表名 CHANGE COLUMN 原名 新名 数据类型 ;
		ALTER TABLE lc_course  CHANGE COLUMN teacher  lecture varchar(100) ;
```

### 插入


```mysql
-- 向表格插入数据 一条记录
	
	INSERT INTO 表名称 VALUES (值1，值2，...);

-- 	或者

	INSERT INTO 表名称 (列1，列2) VALUES (值1，值2) ;

-- 	例：

	INSERT INTO course VALUES(1,'install linux',32,'nash_su','Basic');
	
	INSERT INTO course  (id,course_name,category) VALUES (2,'GNOME','Basic') ;
```

### 查询


```mysql
-- 查询数据

	SELECT 列名1，列名2  FROM 表名称;

	SELECT * FROM course 表中所有信息 ; （查询所有数据）

-- 按条件查询数据

	SELECT 列名 FROM 表名称 WHERE 列名 运算符 值;

	例：

	SELECT * FROM course WHERE course_name='GNOME' ;

	SELECT * FROM course WHERE course_length > 10 ;

-- 支持的运算符

	<> 不等于
	<=
	>=
	BETWEEN		指定范围
	LIKE		某种模式搜索

-- 从表格中删除记录

	DELETE FROM 表名 WHERE 列名 运算符 值 ；
	
	DELETE * FROM 表名 ；（删除表中所有信息）

-- 	例：

	DELETE FROM course  WHERE id = 1 ;
```

### 更新

```mysql
	UPDATE 表名 SET 列名=新值 WHERE 列名=值 ; 

	UPDATE course SET lecture='Lee' WHERE id=3 ; 
```

### 查重

```mysql
-- 删除返回结果重复项 返回结果唯一化

	SELECT DISTINCT 列名 FROM 表名; 

-- 	例：

	SELECT DISTINCT lecture FROM course; 
```

### 排序


```mysql
-- 使用WHERE的逻辑组合

	SELECT * FROM 表名 WHERE 条件1 AND 条件2 ;
	SELECT * FROM 表名 WHERE 条件1 OR 条件2 ;

-- 	例：

	SELECT * FROM course WHERE lecture='nash_su' AND category='Adv';

-- 对查询结果排序

	SELECT * FROM 表名称 ORDER BY 列名 ;		（正序）
	SELECT * FROM 表名称 ORDER BY 列名 DESC; 	（倒序）
```

##  第四课 用户管理


```mysql
-- 默认只有一个root用户

-- 默认保存于mysql保存用户信息   mysql数据库user表中

-- 创建新用户 

	CREATE USER 用户名 IDENTIFIED BY '密码';
	创建后不能登录  因为没有初始化权限

-- 删除用户 

	DROP USER 用户名

-- 重命名用户

	RENAME USER 原用户名 TO 新用户名 ;

-- 修改用户密码

	SET PASSWORD = PASSWORD ('新密码') ;

-- 修改指定用户密码：

	SET PASSWORD FOR 用户名 = PASSWORD('新密码');
```

## 第五课 权限管理

### 权限

```
1 检查用户是否连接诶

2 是否有执行动作的权限
```

### 层级

```
    全局
    数据库
    表
    列
    子程序层级
```

### 权限操作

```sql
-- 通过GRANT 授予权限 REVOKE 撤销权限
-- 授予一个用户权限：

    GRANT ALL PRIVILEGES ON 层级 TO 用户名@主机（远程来源） IDENTIFIED BY 密码 ;

--  例如：
--  全局授权
    GRANT ALL PRIVILEGES ON *.* TO 'nash_su'@'%' IDENTIFIED BY 'linuxcast' ;
    
--  数据库授权
    GRANT ALL PRIVILEGES ON linuxcast.* TO 'nash_su'@'%' IDENTIFIED BY 'linuxcast' ;

-- 撤销用户权限

    REVOKE ALL PRIVILEGES FROM 用户名 ;
授权主机 连接来源

    所有主机    %
    精确的域名或IP    www.linuxcast.net 或 192.168.1.1
    使用*通配符  *.linuxcast.net
    指定网段    192.168.1.0/255.255.255.0
```

### 刷新权限

```sql
-- 最后  刷新权限
FLUSH PRIVILEGES ;
```



## 第六课 备份还原

### 备份


```shell
#使用自带的mysqldump命令	

#备份数据库	

	mysqldump -u root -p 数据库名 > 备份文件.sql

	产生的sql为通用数据库格式
```

### 还原


```shell
#还原数据库

	mysql -u root -p 数据库名 < 备份文件.sql
	
#都是使用了重定向
```


​	  

## 第七课 字符编码

 


	在定义数据库时就需确定使用的编码
	
	如UTF8 GB2312 Big5 Latin
	
	1 不同编码 占用空间不同
	2 数据库与客户端通讯




```mysql 
-- MYSQL默认编码是Latin1
	character set : latin1
	collation : latin1_swedish_ci

-- 可以通过命令查看MYSQL支持的编码
	SHOW CHARACTER SET ;

	常用UTF8（万国） GB2312（简体） Big5（繁体） Latin
	最好使用UTF8 高兼容
```



```mysql
-- 查看当前编码 
	SHOW VARIABLES LIKE 'character_set%' ; 
	SHOW VARIABLES LIKE 'collation%' ;
```




```mysql
-- 创建数据库的时候可以指定使用的编码

	CTEATE DATABASE linuxcast 
		DEFAULT CHARACTER SET utf8
		DEFAULT COLLATE utf8_general_ci ;

-- 也可以通过以下命令修改一个数据库的编码  （可能出现乱码，不常用）

	ALTER DATABASE linuxcast CHARACTER SET utf8 COLLATE utf8_general_ci ;
```



```json
-- 指定创建的默认编码

-- 	修改配置文件

	[client]
	default-character-set=utf8
	[mysql]
	default-character-set=utf8
	[musqld]
	default-character-set=utf8
	collation-server = utf8_unicode_ci
	init-connect='SET NAMES utf8'
	character-set-server = utf8

-- 修改后 重启服务  再次查看

	SHOW VARIABLES LIKE 'character_set%' ;
```

 









