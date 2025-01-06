# NET 7. 0 命令行操作手册

[TOC]



## 建立项目

查看可选模板

```shell
#查看模板类型
$ dotnet new

“dotnet new”命令基于模板创建 .NET 项目。

常用模板包括:
模板名                 短名称        语言        标记
---------------------  ------------  ----------  -------------------
ASP.NET Core Web 应用  webapp,razor  [C#]        Web/MVC/Razor Pages
Blazor Server 应用     blazorserver  [C#]        Web/Blazor         
Windows 窗体应用       winforms      [C#],VB     Common/WinForms
WPF 应用程序           wpf           [C#],VB     Common/WPF
控制台应用             console       [C#],F#,VB  Common/Console
类库                   classlib      [C#],F#,VB  Common/Library

例如:
   dotnet new console

通过以下方式显示模板选项:
   dotnet new console -h
通过以下方式显示已安装的所有模板:
   dotnet new list
通过以下方式显示 NuGet.org 上可用模板:
   dotnet new search web
   
   
#查看模板名
$ dotnet new list	
这些模板已匹配你的输入: 

模板名                                   短名称                     语言        标记
---------------------------------------  -------------------------  ----------  -----------------------------------------
ASP.NET Core gRPC 服务                   grpc                       [C#]        Web/gRPC
ASP.NET Core Web API                     webapi                     [C#],F#     Web/WebAPI
ASP.NET Core Web 应用                    webapp,razor               [C#]        Web/MVC/Razor Pages
ASP.NET Core Web 应用(模型-视图-控制器)  mvc                        [C#],F#     Web/MVC
ASP.NET Core 与 Angular                  angular                    [C#]        Web/MVC/SPA
ASP.NET Core 与 React.js                 react                      [C#]        Web/MVC/SPA
ASP.NET Core 空                          web                        [C#],F#     Web/Empty
Avalonia .NET Core App                   avalonia.app               [C#],F#     Desktop/Xaml/Avalonia/Windows/Linux/macOS
Avalonia .NET Core MVVM App              avalonia.mvvm              [C#],F#     Desktop/Xaml/Avalonia/Windows/Linux/macOS
Avalonia Cross Platform Application      avalonia.xplat             [C#],F#     Desktop/Xaml/Avalonia/Web/Mobile
Avalonia Resource Dictionary             avalonia.resource                      Desktop/Xaml/Avalonia/Windows/Linux/macOS
Avalonia Styles                          avalonia.styles                        Desktop/Xaml/Avalonia/Windows/Linux/macOS
Avalonia TemplatedControl                avalonia.templatedcontrol  [C#],F#     Desktop/Xaml/Avalonia/Windows/Linux/macOS
Avalonia UserControl                     avalonia.usercontrol       [C#],F#     Desktop/Xaml/Avalonia/Windows/Linux/macOS
Avalonia Window                          avalonia.window            [C#],F#     Desktop/Xaml/Avalonia/Windows/Linux/macOS
Blazor Server 应用                       blazorserver               [C#]        Web/Blazor
Blazor Server 应用空                     blazorserver-empty         [C#]        Web/Blazor/Empty
Blazor WebAssembly 应用                  blazorwasm                 [C#]        Web/Blazor/WebAssembly/PWA
Blazor WebAssembly 应用空                blazorwasm-empty           [C#]        Web/Blazor/WebAssembly/PWA/Empty
dotnet gitignore 文件                    gitignore                              Config
Dotnet 本地工具清单文件                  tool-manifest                          Config
EditorConfig 文件                        editorconfig                           Config
global.json file                         globaljson                             Config
MSTest Test Project                      mstest                     [C#],F#,VB  Test/MSTest
MVC ViewImports                          viewimports                [C#]        Web/ASP.NET
MVC ViewStart                            viewstart                  [C#]        Web/ASP.NET
NuGet 配置                               nugetconfig                            Config
NUnit 3 Test Item                        nunit-test                 [C#],F#,VB  Test/NUnit
NUnit 3 Test Project                     nunit                      [C#],F#,VB  Test/NUnit
Razor 类库                               razorclasslib              [C#]        Web/Razor/Library
Razor 组件                               razorcomponent             [C#]        Web/ASP.NET
Razor 页面                               page                       [C#]        Web/ASP.NET
Web 配置                                 webconfig                              Config
Windows 窗体应用                         winforms                   [C#],VB     Common/WinForms
Windows 窗体控件库                       winformscontrollib         [C#],VB     Common/WinForms
Windows 窗体类库                         winformslib                [C#],VB     Common/WinForms
WPF 应用程序                             wpf                        [C#],VB     Common/WPF
WPF 用户控件库                           wpfusercontrollib          [C#],VB     Common/WPF
WPF 类库                                 wpflib                     [C#],VB     Common/WPF
WPF 自定义控件库                         wpfcustomcontrollib        [C#],VB     Common/WPF
xUnit Test Project                       xunit                      [C#],F#,VB  Test/xUnit
协议缓冲区文件                           proto                                  Web/gRPC
控制台应用                               console                    [C#],F#,VB  Common/Console
类库                                     classlib                   [C#],F#,VB  Common/Library
解决方案文件                             sln,solution                           Solution
辅助角色服务                             worker                     [C#],F#     Common/Worker/Web


```

拟建一个Console命令行项目

```shell
#建立工程  ConsoleApp
$ dotnet new console -n ConsoleApp

#运行工程  ConsoleApp
$ dotnet run --project ConsoleApp

#以 release 方式运行   即为 #if DEBUG #else #endif 切换操作
$ dotnet run -c Release
 
#仅构建不运行 
$ dotnet build
```

 

### 安装第三方模块

```shell
# 安装 Newtonsoft.Json 版本13.0.0
$ dotnet add package Newtonsoft --version 13.0.0
#默认安装 Newtonsoft.Json 最新版本
$ dotnet add package Newtonsoft.Json 
```

 这里的安装也可以直接编辑工程的csproj ，构建时dotnet会自动进行环境的还原安装；

```xml
<ItemGroup>
  <PackageReference Include="Newtonsoft.Json" Version="13.0.3" />
</ItemGroup>
```



### 附：主工程代码

Porgram.cs

```c#
// See https://aka.ms/new-console-template for more information

using Newtonsoft.Json;

#if DEBUG
Console.WriteLine("Hello, World! debug");
#else
Console.WriteLine("Hello, World! release");
#endif

var student = new Student(1, "sfe", "A");
var json = JsonConvert.SerializeObject(student);
Console.WriteLine(json);

public class Student
{

    public Student(int _id, string _name, string _grade)
    {
        this.id = _id;
        this.name = _name;
        this.grade = _grade;
    }
    public int id { get; set; }
    public string name { get; set; }
    public string grade { get; set; }
} 
```

使用上述命令行运行即可；



## XUnit测试项目

### 建立项目

建立一个xunit的测试项目

```shell
$ dotnet new xunit -n ConsoleApp.Test
 
#添加引用
$ dotnet add ConsoleApp.Test reference ConsoleApp

#构建
$ cd ConsoleApp.Test
$ dotnet build
```

此处引用其他工程结果也可直接编辑csproj

```xml
<ItemGroup>
  <ProjectReference Include="..\ConsoleApp\ConsoleApp.csproj" />
</ItemGroup>
```

运行测试项目

```shell
#NET 7.0 以前采用方法
$ dotnet.exe test ConsoleApp.Test

#NET 7.0 方法
$ cd ConsoleApp.Test
$ dotnet test 
```

 

### 使用实例

在主工程ConsoleApp中创建文件 StringUtils.cs

```c#
namespace ConsoleApp;
public static class StringUtils{
    public static string  Reversed(this string s){
        var chars = s.ToCharArray();
        Array.Reverse(chars);
        return new string(chars);
    }
}
```

 在测试工程ConsoleApp.Test中的UnitTest1.cs文件中写入

```c#
using ConsoleApp;
namespace ConsoleApp.Test;

public class UnitTest1
{
    [Fact]
    public void Test_StringUtils_Reversed()
    {
        var testStr = "hello";
        var reversed = StringUtils.Reversed(testStr );
        Assert.Equal("olleh",reversed);
    }
}
```

然后使用上述命令行操作即可



## 解决方案

建立一个解决方案，将所有工程都纳入解决方案内部管理；

```shell
#建立解决方案
$ dotnet new sln -n ConsoleApp
#将文件夹下的工程都放入一个解决方案文件
$ dotnet sln add ConsoleApp
$ dotnet sln add ConsoleApp.Test
```

 

## git管理

```shell
$ git init 
$ dotnet new gitignore
```



## 部署

### ASP-NET linux部署

VS工程方面，进入工程目录，执行生成

```shell
$  dotnet  publish --configuration Release --runtime linux-x64
```



#### linux内安装环境

```shell
$ wget https://packages.microsoft.com/config/ubuntu/22.04/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
#ubuntu 22.04 视linux版本决定
$ sudo dpkg -i packages-microsoft-prod.deb
$ rm packages-microsoft-prod.deb
```

安装net sdk或runtime

```shell
#sdk
$ sudo apt-get update
$ sudo apt-get install -y dotnet-sdk-6.0
#runtime
$ sudo apt-get install -y aspnetcore-runtime-6.0
```

转到webapi的发布文件目录，并启动

```shell
#进入
$ cd /var/www/mywebapi
$ sudo chmod 755 * 
#启动
$ dotnet mywebapi.dll
```

注意如果非本机访问，需要对监听地址指定，如果要完全开放地址，可以在启动应用程序之前设置环境变量，如下

```shell
$ set ASPNETCORE_URLS=http://0.0.0.0:5000
```

这样外部访问就不会refuse了

#### 系统服务

为了使Web API能够在后台运行并自动重启，可以将其创建为系统服务

```shell
$ sudo nano /etc/systemd/system/mywebapi.service
```

```ini
[Unit]
Description=My Web API Service

[Service]
WorkingDirectory=/var/www/mywebapi
ExecStart=/usr/bin/dotnet /var/www/mywebapi/mywebapi.dll
Restart=always
RestartSec=10
KillSignal=SIGINT
SyslogIdentifier=mywebapi
User=$USER
Environment=ASPNETCORE_ENVIRONMENT=Production
Environment=DOTNET_PRINT_TELEMETRY_MESSAGE=false

[Install]
WantedBy=multi-user.target
```

```shell
$ sudo systemctl daemon-reload
$ sudo systemctl enable mywebapi.service
$ sudo systemctl start mywebapi
```

#### Nginx反向代理

如果需要通过HTTP访问Web API，可以安装Nginx作为反向代理服务器

```shell
$ sudo apt update
$ sudo apt install nginx
```

配置Nginx

```shell
$ sudo nano /etc/nginx/sites-available/default
```

在`server`块中添加以下配置

```json
location / {
    proxy_pass http://localhost:5000; # 假设Web API运行在5000端口
    proxy_http_version 1.1;
    proxy_set_header Upgrade $http_upgrade;
    proxy_set_header Connection keep-alive;
    proxy_set_header Host $host;
    proxy_cache_bypass $http_upgrade;
}
```

重启Nginx

```shell
$ sudo systemctl restart nginx
```













