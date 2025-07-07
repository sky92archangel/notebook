# AspNetCore项目Docker部署



[TOC]





## 发布项目

进入某工程

发布linux支持的aspnet项目

```shell
dotnet publish -c Release -r linux-x64 --self-contained false -o ./publish
```

- `-c Release`：使用 Release 配置。

- `-r linux-x64`：指定目标平台为 Linux x64。

- `--self-contained false`：轻量化打包，包内无运行时，所以依赖 Linux 上的 .NET 运行时。

- `-o ./publish`：将输出文件存储在 `publish` 目录中

  

  注意：如果`--self-contained true` 那么可以直接放入linux运行，但是打包的结果比较大

  ```shell
  dotnet publish -c Release -r linux-x64 --self-contained false -o ./publish_light
  dotnet publish -c Release -r linux-x64 --self-contained true  -o ./publish_heavy
  ```

  

## 建立镜像

```dockerfile

# 使用基础镜像
FROM mcr.microsoft.com/dotnet/aspnet:8.0

# 设置工作目录为/app
WORKDIR /app

# 复制项目文件（取消注释并调整路径，或使用绑定挂载）
#COPY . .

# 启动bash shell（使用/bin/bash -c保持容器运行）
CMD ["/bin/bash", "-c", "while true; do sleep 1000; done"]

```

这个 Dockerfile 用于构建一个基于.NET 8.0 运行时的容器镜像，主要用于开发或调试场景（而非直接运行应用）。以下是各部分的详细解释：

### **1. 基础镜像选择**

```dockerfile
FROM mcr.microsoft.com/dotnet/aspnet:8.0
```

- [**mcr.microsoft.com/dotnet/aspnet:8.0**](http://mcr.microsoft.com/dotnet/aspnet:8.0)：这是微软官方提供的.NET 8.0 运行时镜像，包含运行[ASP.NET](https://ASP.NET) Core 应用所需的全部依赖（如 Kestrel 服务器、.NET 运行时等）。

- 选择此镜像的好处：无需手动安装.NET 运行时，直接基于官方优化过的环境构建，兼容性和安全性更有保障。

### **2. 设置工作目录**

```dockerfile
WORKDIR /app
```

- **WORKDIR /app**：指定容器内的工作目录为/app。后续所有命令（如COPY、CMD）都会默认在此目录下执行。

- 作用：规范文件存放路径，避免容器内文件混乱，便于后续操作（如进入容器后直接在/app目录工作）。

### **3. 复制项目文件（注释状态）**

```dockerfile
#COPY . .
```

- 这行命令被注释掉了，原本的作用是将宿主机当前目录下的所有文件复制到容器内的/app目录（因WORKDIR已指定）。

- **为何注释**：结合后续的CMD命令可知，这个镜像可能用于**开发场景**，通过**卷挂载**（-v参数）动态加载宿主机文件，而非在构建时固定复制（方便代码修改后无需重新构建镜像）。

### **4. 启动命令（核心）**

```dockerfile
CMD ["/bin/bash", "-c", "while true; do sleep 1000; done"]
```

- 这是容器启动时执行的命令，作用是**让容器保持运行状态而不退出**：

- - /bin/bash -c：通过 bash 执行后续命令。

- - while true; do sleep 1000; done：一个无限循环，每 1000 秒（约 16 分钟）休眠一次，确保容器不会因为命令执行完毕而退出。

- **设计目的**：此镜像不直接运行应用，而是提供一个 “待命” 状态的容器，方便开发者通过docker exec进入容器，手动执行命令（如启动应用、调试代码等）。

#### **镜像的典型用途**

这个 Dockerfile 构建的镜像**不适合生产环境**，主要用于以下场景：

1. **开发调试**：通过卷挂载将本地代码映射到容器的/app目录，进入容器后手动运行dotnet run或dotnet 应用.dll，实时查看代码修改效果。

1. **环境验证**：测试.NET 8.0 运行时环境是否正常，或检查依赖是否缺失。

1. **临时操作**：需要在容器内执行额外命令（如文件修改、配置调整）后再启动应用。

    

### **5. 构建镜像**

**构建镜像**：

```shell
docker build -t my-dotnet-dev:8.0 -f Dockerfile .
```



### **如何使用此镜像**

1. 运行容器**（结合卷挂载）：

```shell
docker run -d \
  -v /本地项目路径:/app \  # 将本地代码映射到容器的/app目录
  -p 5000:8080 \  # 端口映射（可选，根据应用需求）
  --name dev-container \
  my-dotnet-dev:8.0
```

1. **进入容器手动操作**：

```shell
docker exec -it dev-container bash  # 进入容器的bash终端
cd /app  # 已在WORKDIR中，可省略
dotnet run  # 手动启动应用（假设映射的本地代码是ASP.NET Core项目）
```

### **与生产环境镜像的区别**

生产环境的 Dockerfile 通常会：

- 取消CMD的休眠循环，改为直接运行应用（如CMD ["dotnet", "应用.dll"]）。

- 启用COPY命令，将发布后的应用文件复制到容器内（确保镜像包含完整应用）。

- 可能添加非 root 用户、健康检查等配置，增强安全性和可维护性。

### **总结**

这个 Dockerfile 的核心是构建一个 “待命状态” 的.NET 8.0 运行时环境，通过无限循环保持容器运行，方便开发者动态挂载代码并手动操作。适合开发、调试阶段使用，不建议直接用于生产部署。

如果需要将其改为生产环境镜像，只需修改CMD为应用启动命令，并取消COPY的注释（或使用发布后的文件）即可。

 

## 建立容器

从镜像建立容器并启动

```shell
docker run -d \
  -v /mnt/local_server_dir/:/app \
  -p 9020:8080 \
  -e ASPNETCORE_HTTP_PORTS=8080 \
  -e ASPNETCORE_URLS="http://0.0.0.0:8080" \
  container_name:0.1 \
  dotnet XXX.dll
```

这条命令使用 Docker 启动了一个运行 [ASP.NET](https://ASP.NET) Core Web API 的容器，以下是对各部分的详细解释：

### **命令分解**

```shell
docker run -d \
  -v /mnt/local_server_dir/:/app \
  -p 9020:8080 \
  -e ASPNETCORE_HTTP_PORTS=8080 \
  -e ASPNETCORE_URLS="http://0.0.0.0:8080" \
  container_name:0.1 \
  dotnet XXX.dll
```

### **参数详解**

1. **-d**

以**守护进程模式**运行容器，即容器在后台运行，不会阻塞终端。

1. **-v /mnt/local_server_dir/:/app**

**挂载卷**：将宿主机的 /mnt/local_server_dir/ 目录挂载到容器内的 /app 目录。

- - 容器内的应用可以直接访问宿主机的文件。
  - **宿主机的 /mnt/local_server_dir/ 目录 是webapi程序的集中所在地**

- - 常用于开发环境或需要持久化数据的场景。

1. **-p 9020:8080**

**端口映射**：将宿主机的 **9020 端口** 映射到容器内的 **8080 端口**。

- - 外部访问 http://宿主机IP:9020 会被转发到容器内的 http://0.0.0.0:8080。

1. **-e ASPNETCORE_HTTP_PORTS=8080**

设置环境变量 ASPNETCORE_HTTP_PORTS 为 8080，告知 [ASP.NET](https://ASP.NET) Core 应用监听该端口。

- - 但此变量在 .NET 6+ 中已被弃用，建议使用 ASPNETCORE_URLS。

1. **-e ASPNETCORE_URLS="**[**HTTP://0.0.0.0:8080**](http://HTTP://0.0.0.0:8080)**"**

设置环境变量 ASPNETCORE_URLS，强制应用监听 http://0.0.0.0:8080（即所有网络接口的 8080 端口）。

- - **注意**：URL 中的 HTTP:// 应改为小写 http://（HTTP 协议不区分大小写，但规范写法是小写）。

1. **container_name:0.1**

指定要运行的 Docker 镜像及其标签。

1. **dotnet xxx.dll**

**覆盖默认命令**：

- - Docker 镜像的默认启动命令通常是 dotnet 主程序.dll。

- - 这里显式指定dotnet xxx.dll，等效于执行 dotnet xxx.dll。

### **潜在问题**

1. **端口配置冲突**：

同时设置了 ASPNETCORE_HTTP_PORTS 和 ASPNETCORE_URLS，后者会覆盖前者。建议仅保留 ASPNETCORE_URLS。

1. **URL 大小写问题**：

ASPNETCORE_URLS 中的 HTTP:// 应改为 http://，避免可能的解析问题。

1. **HTTPS 重定向警告**：

如果应用中启用了 HTTPS 重定向中间件（app.UseHttpsRedirection()），但未配置 HTTPS 端口，会产生警告（参考之前的讨论）。

### **改进建议**

优化后的命令：

```
docker run -d \
  -v /mnt/local_server_dir/:/app \
  -p 9020:8080 \
  -e ASPNETCORE_URLS="http://0.0.0.0:8080" \  # 修正为小写 http
  container_name:0.1 \
  dotnet xxx.dll  # 显式使用 dotnet 命令
```

如果需要禁用 HTTPS 重定向，确保在 Program.cs 中注释掉相关代码：

```
// app.UseHttpsRedirection();  // 注释此行以禁用 HTTPS 重定向
```

### **验证方法**

1. **检查容器状态**：

```
docker ps  # 查看运行中的容器
```

1. **访问 API**：

```
curl http://localhost:9020/api/values  # 替换为实际 API 路径
```

1. **查看容器日志**：

```
docker logs <容器ID或名称>
```

通过上述配置，容器内的 [ASP.NET](https://ASP.NET) Core 应用将监听 http://0.0.0.0:8080，并通过宿主机的 9020 端口对外提供服务。

