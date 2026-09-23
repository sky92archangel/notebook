# uv 使用手册

> 环境：Windows 11 + Git Bash（MINGW64），uv 最新稳定版
> 本文以一次真实的从零实操为主线，前半部分（一~四章）为实测记录，后半部分（五~十五章）为进阶补全。

---

## 一、环境准备与项目初始化

### 1.1 创建项目目录并初始化

```bash
zhouht@sky92 MINGW64 ~
$ cd /e/WORKSPACE/CODE_PYTHON/uv_test/

zhouht@sky92 MINGW64 /e/WORKSPACE/CODE_PYTHON/uv_test
$ uv init --no-package
Initialized project `uv-test`
```

`uv init --no-package` 创建一个**纯脚本项目**（不打包、不可发布，适合工具脚本和试验代码）。生成的文件：

```bash
$ ll
total 2
-rw-r--r-- 1 zhouht 197121  85  9月 23 09:59 main.py
-rw-r--r-- 1 zhouht 197121 153 9月 23 09:59 pyproject.toml
-rw-r--r-- 1 zhouht 197121   0 9月 23 09:59 README.md
```

同时生成的还有 `.gitignore` 和 `.python-version`：

```bash
$ cat .gitignore
# Python-generated files
__pycache__/
*.py[oc]
build/
dist/
wheels/
*.egg-info

# Virtual environments
.venv

$ cat .python-version
3.12
```

### 1.2 项目配置文件 pyproject.toml

```bash
$ cat pyproject.toml
[project]
name = "uv-test"
version = "0.1.0"
description = "Add your description here"
readme = "README.md"
requires-python = ">=3.12"
dependencies = []
```

要点：
- `requires-python = ">=3.12"` 与 `.python-version`（`3.12`）共同决定解释器版本；
- `dependencies = []` 是声明**约束**的地方，装包后这里会自动出现条目；
- 每次 `uv add` 装包后，uv 会同时生成/更新 `uv.lock`（精确锁定文件）。

> **小提示**：Git Bash 下清屏用 `clear`。实测中的报错：
> ```bash
> $ cls
> bash: cls: command not found
> ```
> `cls` 是 Windows CMD 的命令，在 Git Bash 里不存在。

---

## 二、创建虚拟环境

```bash
$ uv venv
Using CPython 3.12.13
Creating virtual environment at: .venv
Activate with: .venv\Scripts\activate
```

`uv venv` 按 `.python-version` 指定的 3.12 创建 `.venv`（自动挑选本机已安装的 CPython 3.12.13）。

> **两条路线，任选其一，建议后者**：
> 1. **手动路线**：`uv venv` 创建后自行 `source .venv/Scripts/activate`，之后像传统 Python 项目一样用 `python` / `pip`；
> 2. **`uv run` 路线（推荐）**：不手动激活，一切命令交给 `uv run`（见第六章）。`uv run` 会自动保证环境与 pyproject.toml + uv.lock 同步，省去手动管理的麻烦。

---

## 三、添加依赖

### 3.1 添加第一个依赖

```bash
$ uv add requests
Resolved 6 packages in 2.13s
Prepared 3 packages in 578ms
Installed 5 packages in 129ms
 + certifi==2026.7.22
 + charset-normalizer==3.5.1
 + idna==3.20
 + requests==2.34.2
 + urllib3==2.8.0
```

`uv add` 一次完成三件事：把 `requests` 写入 `pyproject.toml` 的 `dependencies` → 解析并更新 `uv.lock` → 安装进 `.venv`。

> 安装时若看到如下警告：
> ```
> warning: Failed to hardlink files; falling back to full copy.
> ```
> 这是因为 uv 的缓存目录（默认在 C 盘）与项目目录（E 盘）不在同一文件系统，硬链接不可用。不影响正确性，解决方案见 13.2 与 14.3。

### 3.2 继续添加依赖

```bash
$ uv add numpy
Resolved 7 packages in 791ms
Installed 1 package in 3.53s
 + numpy==2.5.3

$ uv add sympy
Resolved 9 packages in 1.86s
Prepared 2 packages in 3.21s
Installed 2 packages in 2.75s
 + mpmath==1.3.0
 + sympy==1.14.0
```

> **注意**：`uv sympy` 会报错：
> ```bash
> $ uv sympy
> error: unrecognized subcommand 'sympy'
> ```
> uv 没有"直接装包"的子命令，添加项目依赖一律用 `uv add`。如果只是想临时用一下某个工具而不加入项目，用 `uvx`（见第九章）。

---

## 四、查看依赖树：uv tree

```bash
$ uv tree
Resolved 7 packages in 1ms
uv-test v0.1.0
├── numpy v2.5.3
└── requests v2.34.2
    ├── certifi v2026.7.22
    ├── charset-normalizer v3.5.1
    ├── idna v3.20
    └── urllib3 v2.8.0
```

```bash
$ uv tree
Resolved 9 packages in 1ms
uv-test v0.1.0
├── numpy v2.5.3
├── requests v2.34.2
│   ├── certifi v2026.7.22
│   ├── charset-normalizer v3.5.1
│   ├── idna v3.20
│   └── urllib3 v2.8.0
└── sympy v1.14.0
    └── mpmath v1.3.0
```

依赖树实时反映 `pyproject.toml` 的声明状态，适合检查依赖关系、排查版本冲突。

> 至此完成了 uv 的最小闭环：`uv init` → `uv add` → `uv tree`。
> 接下来是进阶部分。

---

## 五、依赖管理进阶

### 5.1 移除依赖

```bash
$ uv remove numpy
Resolved 7 packages in 412ms
Uninstalled 1 package in 209ms
 - numpy==2.5.3
```

`pyproject.toml` 中的 `dependencies` 列表会同步删除该条目，并重新解析锁定。

### 5.2 开发依赖（dev dependencies）

测试框架、linter、格式化工具等只在开发环境使用的依赖，用 `--dev`（或 `-d`）添加：

```bash
$ uv add --dev pytest ruff
Resolved 11 packages in 1.12s
Installed 3 packages in 1.44s
 + pluggy==1.6.0
 + pytest==9.0.2
 + ruff==0.14.2
```

添加后 `pyproject.toml` 中会生成 `[dependency-groups]` 段：

```toml
[dependency-groups]
dev = [
    "pytest>=9.0.2",
    "ruff>=0.14.2",
]
```

> 惯例：只有开发期工具进 `--dev`；运行期必需的库一律进 `dependencies`。

### 5.3 自定义依赖组

可以给 CI、文档、 notebooks 等场景建独立依赖组：

```bash
$ uv add --group docs mkdocs
```

安装时按需引入：

```bash
$ uv sync --group docs        # 同步时包含 docs 组
$ uv sync --all-groups        # 包含全部组
$ uv sync --no-group docs     # 排除某个组
```

### 5.4 指定版本约束

```bash
$ uv add "requests>=2.32"           # 下限
$ uv add "django<5.0"               # 上限
$ uv add "numpy==2.5.3"             # 精确锁定
$ uv add requests@2.34.2            # @ 语法，等价于 requests==2.34.2
$ uv add git+https://github.com/user/repo   # 直接从 git 安装
```

> 建议：库本身给宽松约束（`>=`），应用项目交给 `uv.lock` 做精确锁定——这是 uv 的核心哲学：**约束与锁定分离**。

### 5.5 与 requirements.txt 互操作

```bash
$ uv add -r requirements.txt        # 导入并转写到 pyproject.toml
$ uv export -o requirements.txt     # 导出（默认含哈希，生产部署用）
$ uv export --no-hashes -o requirements.txt   # 不带哈希（兼容老工具）
$ uv export --dev -o requirements-dev.txt     # 含开发依赖
```

### 5.6 升级依赖

```bash
$ uv lock --upgrade                 # 升级所有可升级的包，重写 uv.lock
$ uv lock --upgrade-package requests  # 只升级 requests（及其必要依赖）
$ uv sync --upgrade-package numpy   # 升级并立即安装
```

---

## 六、运行项目：uv run

### 6.1 基本用法

```bash
$ uv run python main.py
Hello from uv-test!
```

`uv run` 的关键行为：**自动确保环境与 pyproject.toml + uv.lock 一致**（必要时自动安装缺失依赖、自动更新 .venv），然后在该环境中执行命令。因此——

> **项目工作流下几乎不需要手动激活虚拟环境。** 日常用法就是 `uv run python ...` / `uv run pytest` / `uv run ruff check`。

### 6.2 如果习惯激活虚拟环境

```bash
# Git Bash (MINGW64)
$ source .venv/Scripts/activate

# CMD
$ .venv\Scripts\activate.bat

# PowerShell
$ .venv\Scripts\Activate.ps1
```

激活后 `python` / `pip` 指向项目环境。但注意：手动激活后 uv 不会替你保证环境同步，改了依赖要记得 `uv sync`。

### 6.3 一次性脚本与内联依赖（PEP 723）

单个脚本文件也可以声明依赖，无需建项目：

```python
# analyze.py
# /// script
# requires-python = ">=3.12"
# dependencies = ["numpy", "matplotlib"]
# ///
import numpy as np
import matplotlib.pyplot as plt
...
```

```bash
$ uv run analyze.py      # uv 自动创建临时环境并运行，不污染当前项目
```

初始化此类脚本：`uv init --script analyze.py --no-package`（或手写头部注释块）。

---

## 七、锁定与同步：uv.lock 与 uv sync

### 7.1 三个文件的分工

| 文件 | 作用 | 是否提交 git |
|---|---|---|
| `pyproject.toml` | 声明**约束**（>=、<、组） | ✅ 提交 |
| `uv.lock` | 记录**精确解析结果**（版本+哈希） | ✅ 提交（应用项目） |
| `.venv` | 实际环境 | ❌ 不提交（已在 .gitignore） |

### 7.2 常用命令

```bash
$ uv lock                 # 只解析并生成/更新 uv.lock
$ uv sync                 # 让 .venv 与 lock 完全一致（会卸载多余包）
$ uv sync --locked        # CI 用：lock 与 pyproject 不一致则报错，而不是悄悄更新
$ uv sync --frozen        # CI 用：完全不动 lock，按现状安装
```

> CI 推荐：`uv sync --locked && uv run pytest`。本地开发随意，`uv add` 会自动联动 lock。

### 7.3 只锁定不安装的场景

Docker 构建中常见两段式：

```dockerfile
COPY pyproject.toml uv.lock ./
RUN uv sync --locked --no-install-project
COPY . .
RUN uv sync --locked
```

---

## 八、Python 版本管理：uv python

uv 可以自己下载、管理多版本 Python，无需先装 python.org 官方包。

```bash
$ uv python list                  # 列出可用版本（含已下载的）
$ uv python install 3.13          # 下载并安装 CPython 3.13
$ uv python install 3.12 3.13     # 一次装多个
$ uv python pin 3.13              # 把 .python-version 改写为 3.13
$ uv python find 3.12             # 打印该版本解释器路径
```

`uv venv` / `uv init` 会按 `.python-version` 自动选取解释器；本地没有时会询问是否自动下载（`uv python download` 或在命令中加 `--python 3.13` 指定）。

> 与 conda 的关系：二选一管理解释器，不要混用。uv 的模型是"按项目 pin 精确小版本"。

---

## 九、工具安装：uv tool 与 uvx

和项目无关的**全局命令行工具**（ruff、black、httpie、poetry 等），不要装进项目依赖，用 `uv tool`：

```bash
$ uv tool install ruff            # 安装到独立环境，暴露 ruff 命令
$ uv tool install black
$ uv tool upgrade ruff            # 升级某个工具
$ uv tool upgrade --all           # 全部升级
$ uv tool list                    # 查看已装工具
$ uv tool uninstall ruff

$ uvx ruff check .                # 临时运行（不安装，跑完即弃）
$ uvx --from ruff ruff@latest check .   # 指定版本临时运行
```

> `uvx` 是 `uv tool run` 的别名。适合"偶尔用一次的 CLI"，例如 `uvx httpie GET api.example.com`。

---

## 十、pip 兼容接口：uv pip

uv 提供了对 pip 接口的高性能替代，用于**尚未迁移到 pyproject 工作流**的场景（老项目、CI 脚本）：

```bash
$ uv pip install requests         # 快 10–100 倍的 pip install
$ uv pip install -r requirements.txt
$ uv pip compile requirements.in -o requirements.txt   # pip-tools 的替代品
$ uv pip sync requirements.txt    # 让环境与文件完全一致
$ uv pip list
$ uv pip show requests
$ uv pip freeze
```

> 注意区分两套命令：`uv add/remove/sync/lock`（项目工作流，读写 pyproject.toml + uv.lock）与 `uv pip install/compile/sync`（传统工作流，只操作环境）。**同一项目不要混用两套心智模型**。

---

## 十一、构建与发布：uv build / uv publish

前文用 `uv init --no-package` 创建的是**纯脚本项目**（无打包配置）。要发布成库，需要打包模式：

```bash
$ uv init mylib                   # 默认即 package 模式（生成 src/mylib/__init__.py）
$ uv build                        # 生成 dist/mylib-0.1.0.tar.gz 与 .whl
$ uv publish                      # 上传到 PyPI（需先配置凭据）
```

### 11.1 把现有 --no-package 项目转为可打包

在 `pyproject.toml` 中补打包段（默认后端 hatchling）：

```toml
[build-system]
requires = ["hatchling"]
build-backend = "hatchling.build"

[tool.hatch.build.targets.wheel]
packages = ["."]
```

然后 `uv build` 即可。

### 11.2 发布配置

```bash
$ uv publish --token pypi-...              # 命令行传 token
# 或在 ~/.pypirc / UV_PUBLISH_TOKEN 环境变量中配置
```

---

## 十二、工作区（Workspaces）

monorepo 场景：根目录 `pyproject.toml` 声明成员包，根 `uv.lock` 统一锁定整仓依赖：

```toml
# 根 pyproject.toml
[tool.uv.workspace]
members = ["packages/*"]
```

```bash
$ uv sync                 # 一次装齐所有成员
$ uv run --package pkg-a pytest   # 在指定成员环境中运行
```

适合"一个内核 + 多个插件包"的仓库结构。

---

## 十三、缓存、镜像与环境变量

### 13.1 缓存

- 全局缓存默认在 `%LOCALAPPDATA%\uv\cache`（Windows）。
- `uv cache clean` 清缓存；`uv cache prune` 清无用条目。
- 缓存使**跨项目复用**成为可能：十个项目都依赖 numpy 2.5.3，磁盘上只存一份（通过硬链接）。

### 13.2 常用环境变量

| 变量 | 作用 |
|---|---|
| `UV_LINK_MODE=copy` | 缓存与目标目录在不同文件系统（如 E: 盘项目）时禁用硬链接回退 |
| `UV_INDEX_URL` | 默认包索引，默认 `https://pypi.org/simple` |
| `UV_DEFAULT_INDEX` | 新版推荐写法，同上 |
| `UV_PYTHON` | 指定解释器路径 |
| `UV_CACHE_DIR` | 自定义缓存目录 |
| `UV_PROJECT_ENVIRONMENT` | 自定义项目环境路径（默认 ./.venv） |

### 13.3 使用国内镜像

```bash
$ uv add requests --default-index https://mirrors.aliyun.com/pypi/simple/
```

或写入 `pyproject.toml`（团队共享）：

```toml
[[index]]
url = "https://mirrors.aliyun.com/pypi/simple/"
default = true
```

---

## 十四、常见问题与报错速查

### 14.1 `bash: cls: command not found`

`cls` 是 Windows CMD 的命令，Git Bash 下清屏用：

```bash
$ clear
```

### 14.2 `error: unrecognized subcommand 'sympy'`

`uv` 没有"直接装包"的子命令，添加项目依赖一律走 `uv add`：

```bash
$ uv add sympy          # 正确
$ uv sympy              # 错误，uv 会把它当子命令解析
```

如果只是想**临时用一下**而不加入项目依赖，用 `uvx`：

```bash
$ uvx --from sympy isympy    # 临时环境运行 sympy 的交互 shell
```

### 14.3 `Failed to hardlink files; falling back to full copy`

原因：uv 的缓存目录（C 盘）与项目目录（如 E: 盘）**不在同一文件系统**，硬链接不可用，退化为完整复制。

不影响正确性，仅安装稍慢。消除警告任选其一：

```bash
# 当前会话
$ export UV_LINK_MODE=copy

# 永久生效（Git Bash）
$ echo 'export UV_LINK_MODE=copy' >> ~/.bashrc

# 或：把缓存也放到 E 盘，恢复硬链接（更快、省空间）
$ export UV_CACHE_DIR=/e/WORKSPACE/uv-cache
```

> 推荐第二种方案（把 `UV_CACHE_DIR` 也迁到 E 盘），既消警告又恢复硬链接加速。

### 14.4 `uv run` 报错 "environment is stale"

说明 `.venv` 与 `pyproject.toml`/`uv.lock` 不同步，一般 uv 会自动修复；若反复出现，执行：

```bash
$ uv sync
```

### 14.5 PowerShell 激活脚本被禁止

```powershell
> Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

（仅当前用户放开脚本执行；Git Bash/CMD 无此问题。）

---

## 十五、命令速查表

| 场景 | 命令 |
|---|---|
| 初始化项目（脚本） | `uv init --no-package` |
| 初始化项目（可发布库） | `uv init` |
| 添加依赖 | `uv add requests` / `uv add --dev pytest` |
| 移除依赖 | `uv remove numpy` |
| 查看依赖树 | `uv tree` |
| 升级依赖 | `uv lock --upgrade` / `uv lock -P requests` |
| 运行 | `uv run python main.py` / `uv run pytest` |
| 同步环境 | `uv sync` / `uv sync --locked` |
| 管理 Python | `uv python install 3.13` / `uv python pin 3.13` |
| 全局 CLI 工具 | `uv tool install ruff` / `uvx ruff check` |
| 单文件脚本（带依赖） | `uv run script.py`（PEP 723 头） |
| 构建/发布 | `uv build` / `uv publish` |
| requirements.txt 互导 | `uv add -r requirements.txt` / `uv export -o requirements.txt` |
| 清缓存 | `uv cache clean` |

---

## 附：典型日常循环

```bash
# 新人 clone 项目后
$ git clone <repo> && cd <repo>
$ uv sync                          # 一次性装好与 lock 完全一致的环境

# 日常开发
$ uv add <pkg>                     # 加依赖（自动 lock + 安装）
$ uv run python main.py            # 跑
$ uv run pytest                    # 测
$ git add pyproject.toml uv.lock   # 约束与锁定一起提交
```

> 核心心智模型一句话：**pyproject.toml 说"我要什么"，uv.lock 说"具体是哪个"，uv sync 让环境变成那个样子。日常只需 `uv add` 和 `uv run` 两个命令。**
