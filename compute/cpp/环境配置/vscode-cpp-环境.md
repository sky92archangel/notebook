

该方法仅仅用于简单环境搭建 和初始测试用

复杂多文件debug采用cmake即可

 

准备C/C++编译器

安装vscode



安装中文包



安装C/C++插件  建议1.8.4版本 涉及launch.json的生成



测试代码

```c++
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

int main(){
    printf("Welcome 你好  wel");
    std::cout<<" 你好 Welcome"<<std::endl;
    return 0;
}
```



进行调试运行，选择合适编译器



在当前目录产生 .vscode 文件夹

文件夹内产生launch.json , 在externalConsole处改为true 则可以使用外部命令行显示调试结果

```json
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "g++.exe - 生成和调试活动文件",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": true,  //使用外部命令行显示调试结果
            "MIMode": "gdb",
            "miDebuggerPath": "PATH_TO_mingw64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "将反汇编风格设置为 Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: g++.exe 生成活动文件"
        }
    ]
}
```

添加中文支持  在 args 内增加   "-fexec-charset=GBK"

```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe 生成活动文件",
            "command": "PATH_TO_mingw64\\bin\\g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-fexec-charset=GBK"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        }
    ],
    "version": "2.0.0"
}
```



 