[TOC]

# Serde 到底是什么

**Serde = Serialize + Deserialize**，Rust 生态最主流的**序列化/反序列化框架**。 简单一句话：**把内存里的结构体，和外部数据格式（JSON/Excel/YAML/TOML/Bincode等）互相转换**。

> 不是只做 JSON！Serde 是**框架**，JSON 只是其中一个插件。

## 核心概念

- **序列化（Serialize）**：内存结构体 → 字节/文本（存文件、发网络） `struct User {name:String} → {"name":"abc"}`
- **反序列化（Deserialize）**：文本/字节 → 内存结构体 `{"name":"abc"} → 实例化 User`

Serde 本身**不包含任何格式解析代码**，它只定义一套统一的 trait：

- `Serialize` trait：类型可以被序列化
- `Deserialize` trait：类型可以被反序列化

不同格式靠**独立的 crate** 实现：

| 格式              | crate                   |
| ----------------- | ----------------------- |
| JSON              | `serde_json`            |
| TOML              | `toml`                  |
| YAML              | `serde_yaml`            |
| 二进制            | `bincode`               |
| Excel（calamine） | calamine 内置对接 serde |

## 最常用：derive 宏（自动生成代码）

你之前 Excel 例子里的：

```
#[derive(Debug, Deserialize)]
struct Record {
    name: String,
    age: i32,
    score: f64,
}
```

`#[derive(Deserialize)]` 是 **serde 的宏**，自动帮你实现 `Deserialize` trait。 不用手写解析每行字符串、转类型、赋值给结构体，serde 自动映射。

> 对应的还有 `Serialize`：
>
> ```
> #[derive(Serialize, Deserialize)]
> ```

### Cargo.toml 基础依赖

```
serde = { version = "1.0", features = ["derive"] }
```

`derive` 是开启宏，**几乎必加**。

## 极简 JSON 例子，一看就懂

```
use serde::{Serialize, Deserialize};

#[derive(Debug, Serialize, Deserialize)]
struct User {
    name: String,
    age: u32,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 结构体 → JSON字符串（序列化）
    let u = User{name:"张三".into(), age:25};
    let json_str = serde_json::to_string(&u)?;
    println!("{}", json_str);

    // JSON字符串 → 结构体（反序列化）
    let data = r#"{"name":"李四","age":30}"#;
    let u2: User = serde_json::from_str(data)?;
    println!("{:?}", u2);
    Ok(())
}
```

需要额外加：

```
serde_json = "1.0"
```

## 回到刚才的 calamine + serde

calamine 实现了 serde 的反序列化接口。 所以你可以直接：

> Excel一行单元格数据 → serde自动映射到 Rust struct calamine 内部把表格行包装成 serde 的数据源，**复用同一套 serde 结构体定义**，不用手写单元格类型判断。

这就是为什么非常方便：**同一套结构体，可以同时解析 JSON、TOML、Excel**。

## Serde 关键特点

1. **零成本抽象**：宏在编译期生成代码，运行时几乎无开销
2. **强类型**：类型不匹配直接报错（比如age单元格文本不是数字，反序列化直接返回Err）
3. **生态标准**：Rust几乎所有数据解析库都兼容serde（reqwest、sqlx、calamine、toml等）
4. 可自定义：可以手动实现 `Serialize/Deserialize` trait，自定义解析逻辑（处理特殊格式、日期、空值）

## 容易混淆的点

✅ serde：**框架/抽象层**，定义序列化trait，宏 ✅ serde_json：**JSON后端实现**，依赖serde ❌ serde ≠ JSON库

## 常用 serde 衍生特性（生产高频）

```
#[serde(rename_all = "snake_case")] // 自动大小写映射
#[serde(default)] // 字段缺失用默认值
#[serde(skip)]    // 跳过此字段，不序列化
#[serde(rename = "user_name")] // 自定义字段名
#[serde(deserialize_with = "xxx")] // 自定义解析函数
```

如果你想，我可以写一个 **calamine+serde 带空值容错、日期转换** 的生产级示例。





# Serde 用法大全（Rust，serde 1.0）

> 前置依赖

```
# Cargo.toml
serde = { version = "1.0", features = ["derive"] }
# 常用格式后端（按需引入）
serde_json = "1.0"    # json
toml = "0.8"          # toml
serde_yaml = "0.9"    # yaml
bincode = "1.3"       # 二进制序列化
use serde::{Serialize, Deserialize};
```

> 核心：`Serialize` 序列化（结构体→外部数据）；`Deserialize` 反序列化（外部数据→结构体）。 `#[derive(Serialize, Deserialize)]` 由 proc macro 在**编译期生成实现**，零运行时开销。

------

## 一、基础用法

### 1. 简单结构体

```
#[derive(Debug, Serialize, Deserialize)]
struct User {
    name: String,
    age: u32,
    is_vip: bool,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let u = User {
        name: "alice".into(),
        age: 28,
        is_vip: true,
    };
    // 序列化：struct -> json字符串
    let s = serde_json::to_string_pretty(&u)?;
    println!("{}", s);

    // 反序列化：json字符串 -> struct
    let json_text = r#"{ "name":"bob", "age":30, "is_vip":false }"#;
    let u2: User = serde_json::from_str(json_text)?;
    println!("{:?}", u2);
    Ok(())
}
```

### 2. 枚举（enum）序列化

#### 单元变体

```
#[derive(Debug, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
enum OrderStatus {
    Pending,
    Paid,
    Canceled,
}
```

#### 带数据的枚举（两种风格）

```
// 方式1：外部标签（默认，最常用）
#[derive(Debug, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
enum Msg {
    Text(String),
    Point { x: f64, y: f64 },
}

// 方式2：内部标签（适合json）
#[derive(Debug, Serialize, Deserialize)]
#[serde(tag = "type")]
enum Event {
    Login { uid: u64 },
    Logout,
}
// 输出示例：{"type":"login","uid":123}
```

------

## 二、serde 属性宏（高频，写在struct/enum/字段上）

> 所有属性都放在 `#[serde(...)]`

### 1. 重命名相关

```
#[derive(Debug, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")] // 全局：全部字段下划线命名
struct Student {
    #[serde(rename = "stu_id")] // 单独修改字段名
    id: u64,
    real_name: String,
}
```

可选 `rename_all` 规则：

- `snake_case`：`user_name`（下划线）
- `camelCase`：`userName`
- `PascalCase`：`UserName`
- `kebab-case`：`user-name`

### 2. 跳过字段

```
#[derive(Debug, Serialize, Deserialize)]
struct Data {
    id: u64,
    #[serde(skip)] // 序列化、反序列化都忽略
    temp_cache: String,

    #[serde(skip_serializing)] // 只序列化时跳过，反序列化读取
    only_read: String,

    #[serde(skip_deserializing)] // 只反序列化跳过，序列化输出
    only_write: String,
}
```

### 3. 默认值处理（缺失字段容错，工程最常用）

```
#[derive(Debug, Serialize, Deserialize)]
struct Config {
    #[serde(default)] // 字段缺失，使用类型默认值
    port: u16,

    #[serde(default = "default_timeout")] // 自定义默认函数
    timeout: u64,
}
fn default_timeout() -> u64 { 3000 }
```

> `#[serde(default)]` 放在**struct上**：所有缺失字段全部启用默认值。

### 4. 可选 Option

`Option`：存在则Some，缺失/ null → None

```
#[derive(Debug, Serialize, Deserialize)]
struct Product {
    name: String,
    desc: Option<String>, // 字段不存在或null → None
}
```

### 5. 忽略未知字段（反序列化多余key不报错）

```
#[derive(Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)] // ❌ 严格模式：遇到多余字段直接报错
#[serde(flatten)] // ✅ 把内部结构体平铺到外层
struct Outer {
    id: u64,
    #[serde(flatten)]
    inner: Inner,
}
struct Inner {
    addr: String
}
```

> `flatten`：合并嵌套结构体，不再嵌套json对象。

### 6. 自定义序列化/反序列化函数 `deserialize_with` / `serialize_with`

适合：日期、特殊字符串、Excel单元格特殊转换

```
#[derive(Debug, Serialize, Deserialize)]
struct Record {
    name: String,
    #[serde(deserialize_with = "parse_float_str")]
    price: f64,
}
// 自定义解析函数签名固定格式
fn parse_float_str<'de, D>(de: D) -> Result<f64, D::Error>
where D: serde::Deserializer<'de>
{
    let s = String::deserialize(de)?;
    s.parse().map_err(serde::de::Error::custom)
}
```

### 7. 空字符串特殊处理（常用在Excel/csv）

```
#[serde(default)]
#[serde(deserialize_with = "empty_string_as_none")]
email: Option<String>,
```

------

## 三、容器类型支持（Vec, HashMap）

```
use std::collections::HashMap;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let v = vec![1,2,3];
    let s = serde_json::to_string(&v)?;
    println!("vec:{}", s);

    let mut map = HashMap::new();
    map.insert("k1".to_string(), 99);
    let s2 = serde_json::to_string(&map)?;
    println!("map:{}", s2);
    Ok(())
}
```

------

## 四、手动实现 Serialize / Deserialize（不使用derive宏）

> 当derive宏无法满足场景（动态逻辑）才手写，一般不推荐。

```
use serde::{ser::Serializer, de::Deserializer, Deserialize, Serialize};

struct Wrapper(u32);

impl Serialize for Wrapper {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
        where S: Serializer
    {
        serializer.serialize_u32(self.0)
    }
}
```

------

## 五、serde_json 专属工具（高频）

```
// 1. Value 动态json（无固定结构体，临时用）
use serde_json::Value;
let json_text = r#"{"a":1}"#;
let v: Value = serde_json::from_str(json_text)?;
println!("{}", v["a"]);

// 2. 转为Value，再修改
let mut obj = serde_json::json!{
    {
        "name": "test",
        "count": 10
    }
};
obj["count"] = serde_json::Value::Number(serde_json::Number::from(20));
```

> ⚠️ 生产优先用结构体，`Value` 动态类型性能差、缺少编译期校验。

------

## 六、和 calamine（Excel）联合使用（你之前场景）

```
calamine = {version="0.22", features=["serde"]}
serde = {version="1.0", features=["derive"]}
use calamine::{open_workbook, Xlsx, RangeDeserializerBuilder};
use serde::Deserialize;

#[derive(Debug, Deserialize)]
#[serde(rename_all = "snake_case")]
struct RowItem {
    name: String,
    age: Option<u32>,
    score: f64,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut wb: Xlsx<_> = open_workbook("data.xlsx")?;
    let range = wb.worksheet_range("Sheet1").ok_or("sheet not found")??;
    let iter = RangeDeserializerBuilder::new().from_range(&range)?;
    for r in iter {
        let row: RowItem = r?;
        println!("{:?}", row);
    }
    Ok(())
}
```

原理：calamine 实现了 serde 的 `Deserializer` trait，表格行数据直接喂给serde反序列化。

------

## 七、常用避坑清单

1. **String vs &str**：反序列化**不能用 &str**，必须 `String`；序列化可以用&str。
2. 数字类型：json数字统一解析为f64/Number，反序列到u32溢出会报错。
3. 空值：Excel里空单元格会映射为`None`，用`Option`接收。
4. 枚举：默认外部标签格式；如果对接前端json，经常需要 `#[serde(tag="type")]`。
5. 性能：derive宏是零成本；`serde_json::Value`动态解析有开销，大批量数据尽量用结构体。
6. 循环引用：serde**不支持循环引用结构体**，会报错。

## 八、配套常用扩展crate

- `serde_with`：超级增强库，日期、base64、带格式数字、自定义类型一键支持（生产必装）

```
serde_with = "3"
```

示例：日期解析、十六进制字符串

```
use serde_with::serde_as;
use serde_with::chrono::DateTime;

#[serde_as]
#[derive(Debug, Serialize, Deserialize)]
struct Log {
    #[serde_as(as = "DateTime<serde_with::chrono::Utc>")]
    time: DateTime<chrono::Utc>
}
```

------

## 九、实战模板：带容错、默认值、空值处理的生产模板

```
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
#[serde(default)]
struct BizRecord {
    name: String,
    #[serde(skip_serializing_if = "Option::is_none")] // Option为None时不输出该字段
    remark: Option<String>,
    count: u32,
}
impl Default for BizRecord {
    fn default() -> Self {
        Self {
            name: "".into(),
            remark: None,
            count: 0,
        }
    }
}
```

如果你想要，我可以：

1. 单独写一份 **serde_with 完整示例（日期、空字符串、数字兼容）**，或者
2. 写一个 **calamine+serde+serde_with 处理Excel日期/空单元格** 的成品代码。