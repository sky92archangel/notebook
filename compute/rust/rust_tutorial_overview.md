# Rust 教学项目全览：代码详解与教学指南



> 本教程共 **29 个可运行项目**，分为基础入门、Web 框架、实战项目、核心概念深入四大模块。
> 每个项目配有完整的可运行代码和详细中文解释。

---



[TOC]

# 第一篇：基础入门（chapter01–16）

---

## 第 1 章：Hello, World! — `println!` 格式化输出

**文件：** `chapter01_hello/src/main.rs`

### 最小 Rust 程序

```rust
fn main() {
    println!("Hello, World!");
}
```

- `fn` 定义函数，`main` 是可执行程序入口
- `println!` 的 `!` 表示这是一个**宏**（macro），在编译期展开，可以做参数类型检查
- 对比 Go：Go 需要 `package main` + `func main()`，Rust 只需 `fn main()`

### 格式化占位符

```rust
let name = "Rust";
let year = 2026;
println!("语言: {}, 年份: {}", name, year);
```

- `{}` 是通用占位符，要求类型实现 `Display` trait
- 编译期检查格式字符串与参数是否匹配（宏的特性）
- 对比 Go：Go 在运行时检查，Rust 在编译期检查

### Debug 输出 `{:?}` 和 `{:#?}`

```rust
let nums = [1, 2, 3];
println!("数组 debug 输出: {:?}", nums);
println!("数组美化输出: {:#?}", nums);
```

- `{:?}` 使用 `Debug` trait，几乎所有标准库类型都实现了它
- `{:#?}` 美化版，多行缩进显示嵌套结构

### 命名参数与位置参数

```rust
println!("{language} 版本 {version}", language = "Rust", version = "1.85");
println!("{0} 对 {1}, {1} 对 {0}", "甲方", "乙方");
```

- 命名参数避免参数顺序错误
- 位置参数可重复引用同个参数（如上 `{1}` 出现两次）

### 宽度与对齐

```rust
println!("[{:<8}]", "left");    // [left    ]
println!("[{:>8}]", "right");   // [   right]
println!("[{:^8}]", "center");  // [ center ]
println!("[{:05}]", 42);        // [00042]
```

### 标准错误输出

```rust
eprintln!("这行输出到 stderr");
```

### 表达式块作为参数

```rust
println!("计算结果: {}", {
    let a = 10;
    a * 3 + 2  // 块表达式最后一个表达式就是它的值
});
```

- Rust 中几乎所有东西都是表达式，代码块的最后一个表达式（不带分号）就是其返回值

---

## 第 2 章：变量与可变性

**文件：** `chapter02_variables/src/main.rs`

### 不可变变量（默认）

```rust
let x = 5;
// x = 6; // 编译错误：cannot assign twice to immutable variable
```

- `let` 声明的变量**默认不可变**，这是 Rust 最核心的设计哲学之一
- 对比 Go：Go 变量默认可变（`var x = 5; x = 6` 合法）

### 可变变量 `mut`

```rust
let mut y = 5;
y = 6; // 合法
```

- `mut` 关键字显式声明可变性，是一种**意图声明**

### 类型标注与推断

```rust
let a: i32 = 10;     // 显式标注
let b = 20;          // 推断为 i32（默认整型）
let _c: f64 = 3.14;  // f64 是默认浮点类型
let d = 2.5f32;      // 后缀写法
```

### 变量遮蔽（Shadowing）

```rust
let z = 5;
let z = z + 1;   // 新 z = 6（遮蔽旧 z）
let z = z * 2;   // 新 z = 12（再次遮蔽）

let spaces = "   ";      // &str 类型
let spaces = spaces.len(); // usize 类型 —— 合法！可以改变类型
```

- 遮蔽可以在同一作用域用 `let` 重新声明同名变量
- **遮蔽可以改变变量的类型**，而 `mut` 只能改值不能改类型
- 对比 Go：Go 的 `:=` 在同一作用域重复声明会报错

### 常量 `const`

```rust
const MAX_POINTS: u32 = 100_000; // 必须标注类型
```

- `const` 在**编译期求值**，无固定内存地址，每次使用都会内联
- 对比 Go：Go 的 `const` 不要求类型标注，且有 `iota` 自动递增

### 静态变量 `static`

```rust
static APP_NAME: &str = "rust_tutorial";
```

- `static` 有**固定内存地址**，生命周期为整个程序运行期
- `const` 和 `static` 的关键区别：`const` 无内存地址（内联），`static` 有固定地址

### 解构赋值

```rust
let (px, py) = (3, 5);           // 元组解构
let [n1, n2, n3] = [10, 20, 30]; // 数组解构
let (first, _, last) = ("头部", "中间", "尾部"); // 忽略中间
```

- `_` 是通配符，表示"忽略这个值"
- 对比 Go：Go 不支持这样的解构语法

---

## 第 3 章：数据类型

**文件：** `chapter03_datatypes/src/main.rs`

### 整数类型全览

```rust
let i8_v: i8 = -128;          // 范围 -2^7 .. 2^7-1
let u8_v: u8 = 255;           // 范围 0 .. 2^8-1
let i32_v: i32 = 2_147_483_647; // i32 是 Rust 默认整型
let usize_v: usize = 42;      // 集合索引类型
```

### 数字字面量

```rust
let dec = 98_222;     // 十进制，下划线分隔
let hex = 0xff;       // 十六进制
let oct = 0o77;       // 八进制
let bin = 0b1111_0000;// 二进制
let byte = b'A';      // 字节字面量（u8）
```

- 数字字面量可以用 `_` 作为视觉分隔符，不影响值
- 对比 Go：Go 没有 `b'A'` 字节字面量，没有 `0b` 二进制字面量（直到 Go 1.13）

### 整型溢出（重点！）

```rust
let big: u8 = 255;
let wrapped = big.wrapping_add(1);   // 回绕：256 -> 0
let checked = big.checked_add(1);    // 返回 Option：None 表示溢出
let satur = big.saturating_add(1);   // 饱和：255 -> 255
let (result, overflowed) = big.overflowing_add(1); // (0, true)
```

- **Debug 模式**：溢出会 **panic**，让开发者尽早发现问题
- **Release 模式**：补码回绕（wrap around），不 panic，追求性能
- Rust 提供四种显式溢出处理方法
- 对比 Go：Go 始终回绕，没有 debug/release 区别，需手动用 `math.AddUint32` 等

### 字符 `char`：4 字节 Unicode

```rust
let c1 = 'a';
let c2 = '中';       // 中文
let c3 = '🦀';       // Emoji
let c4: char = '\u{1F980}'; // Unicode 转义
println!("char 占 {} 字节", std::mem::size_of::<char>()); // 4
```

- Rust 的 `char` 是 **4 字节 Unicode 标量值**
- 对比 Go：Go 的 `rune`（`int32` 别名）也是 4 字节

### 浮点类型与精度陷阱

```rust
let f32_v: f32 = 3.5;
let f64_v = 2.718281828; // 默认 f64

// NaN 不等于自己
let nan = f64::NAN;
println!("nan != nan ? {}", nan != nan); // true

// 0.1 + 0.2 陷阱
println!("0.1 + 0.2 == 0.3 ? {}", 0.1 + 0.2 == 0.3); // false！
let eps = 1e-9;
let diff: f64 = 0.1 + 0.2 - 0.3;
println!("近似比较: {}", diff.abs() < eps); // true
```

### 元组与单元类型

```rust
let tup: (i32, f64, u8) = (500, 6.4, 1);
let (x, y, z) = tup;            // 解构
println!("tup.0={}", tup.0);    // 点索引

let _unit: () = ();
println!("单元类型大小 = {} 字节", std::mem::size_of::<()>()); // 0
```

- 元组可以聚合不同类型的值，长度固定
- **单元类型 `()`** 是"空元组"，大小为 0 字节
- 对比 Go：Go 的元组（多返回值）只能用于函数返回

### 数组与安全访问

```rust
let arr: [i32; 5] = [1, 2, 3, 4, 5];
let zeros = [0; 5];  // 全部初始化为 0

match arr.get(10) {
    Some(v) => println!("arr[10] = {}", v),
    None => println!("arr.get(10) 安全返回 None，不 panic"),
}
```

- 数组 `[T; N]` 的**长度是类型的一部分**
- `[0; 5]` 是初始化语法
- 直接 `arr[10]` 会 panic，但 `arr.get(10)` 返回 `Option`

### 类型转换

```rust
let int_to_float = 95 as f64;
let float_to_int = 95.9 as i32;  // 截断 -> 95

// 安全转换
match i32::try_from(300i64) { Ok(v) => println!("{}", v), Err(_) => {} }
let result: Result<i32, _> = 50_000_000_000i64.try_into();

// From/Into 甜点语法
let s: String = String::from("hello");
let s2: String = "world".into();
```

- `as` 是简单转换（可能有损），只用于基本类型
- `TryFrom/TryInto` 是安全转换，返回 `Result`
- `From/Into` 是无损转换，实现 `From` 会自动提供 `Into`

### 类型别名

```rust
type Kilograms = f64;
let weight: Kilograms = 72.5;
```

---

## 第 4 章：常量与运算符

**文件：** `chapter04_constants_operators/src/main.rs`

### `const` vs `static`

```rust
const PI: f64 = std::f64::consts::PI;
const MAX_USERS: usize = 10_000;
static VERSION: &str = "v1.0.0";
```

- `const` 编译期内联，无固定内存地址
- `static` 固定内存地址，贯穿整个程序运行期

### 算术运算符与类型约束

```rust
let a = 17;
let b = 5;
println!("除 a / b = {}", a / b);  // 3（整数除法截断）
// let bad = 17 / 5.0; // 编译错误：类型不匹配！
println!("混合: {}", a as f64 / b as f64); // 先转换再运算
```

- Rust 不允许不同类型之间直接运算
- 对比 Go：Go 中 `17 / 5.0` 可通过类型推断正常工作

### 无三目运算符，但用 if-else 表达式

```rust
let age = 20;
let category = if age >= 18 { "成年" } else { "未成年" };
```

- Rust 没有 `? :` 三目运算符，但 `if-else` 本身就是表达式

### 无 `++`/`--` 运算符

```rust
let mut i = 0;
i += 1; // 唯一写法
```

### 范围表达式

```rust
let r1 = 1..=5;  // 包含两端：1,2,3,4,5
let r2 = 0..3;   // 左闭右开：0,1,2
println!("3 在 1..=5 里？ {}", r1.contains(&3));
```

- 对比 Go：Go 没有范围字面量

### 运算符重载（`std::ops`）

```rust
#[derive(Debug, Clone, Copy)]
struct Vec2 { x: f64, y: f64 }

impl std::ops::Add for Vec2 {
    type Output = Vec2;
    fn add(self, rhs: Vec2) -> Vec2 {
        Vec2 { x: self.x + rhs.x, y: self.y + rhs.y }
    }
}
// 之后可以：v1 + v2
```

- Rust 允许通过实现 `std::ops` 中的 trait 来重载运算符
- 编译时多态，零成本抽象
- 对比 Go：Go 完全不支持运算符重载

---

## 第 5 章：控制流

**文件：** `chapter05_control/src/main.rs`

### if 条件必须是 `bool`

```rust
let number = 6;
if number % 4 == 0 {
    println!("{} 能被 4 整除", number);
} else if number % 3 == 0 {
    println!("{} 能被 3 整除", number);
}
```

- Rust 的条件必须是显式的 `bool` 表达式（与 Go 一致）

### `loop` 循环返回值

```rust
let result = loop {
    count += 1;
    if count == 10 {
        break count * 2; // loop 表达式的值是 20
    }
};
```

- `loop` 是 Rust 独有的无限循环，可 `break` 返回值
- 对比 Go：Go 中需要包一层 `func()` 再 `return`

### 循环标签

```rust
'outer: for i in 1..=5 {
    for j in 1..=5 {
        if i * j > 6 {
            break 'outer; // 直接跳出外层循环
        }
    }
}
```

### `match` 表达式

```rust
let value_in_cents = match coin {
    1 => "一分",
    5 => "五分",
    10 => "一角",
    25 => "两角五",
    _ => "其他面值",  // 通配符兜底
};
```

- `match` 是 Rust 最强大的控制流
- **必须穷尽所有可能**（exhaustive），否则编译错误
- 支持范围模式 `1..=3`、或模式 `7 | 11`、绑定 `n @ 8..=12`
- 对比 Go：Go 的 `switch` 不需要穷尽，没有模式匹配

### match 绑定子模式：`@` 语法

```rust
let msg = match dice {
    1..=3 => format!("小 ({})", dice),
    4..=6 => format!("中 ({})", dice),
    7 | 11 => format!("幸运数 {}", dice),
    n @ 8..=12 => format!("大区间 {}", n),
    _ => "未知".to_string(),
};
```

### match 与 `Option`

```rust
fn divide(a: i32, b: i32) -> Option<i32> {
    if b == 0 { None } else { Some(a / b) }
}
match divide(10, 0) {
    Some(v) => println!("结果 = {}", v),
    None => println!("除零！"),
}
```

- Rust 没有 `null`，用 `Option<T>` 表示值可能存在或不存在
- 编译器强制处理 `None` 情况，消灭空指针异常

### `if let` 语法糖

```rust
let favorite: Option<i32> = Some(3);
if let Some(3) = favorite {
    println!("是 3！");
}
if let Some(n) = favorite {
    println!("值是 {}", n);
} else {
    println!("是 None");
}
```

- `if let` 是 `match` 的语法糖，只关心一种模式时省略样板代码

### `let-else` 模式（Rust 1.65+）

```rust
fn describe(opt: Option<i32>) -> String {
    let Some(v) = opt else {
        return "空值".to_string(); // else 必须发散（return/break/panic）
    };
    format!("值是 {}", v * 10)     // v 在此已解包，可直接使用
}
```

- 匹配成功后变量在当前作用域可直接使用
- 对比 Go：Go 需手动 `if v, ok := x.(type); !ok { return }`

---

## 第 6 章：循环

**文件：** `chapter06_loops/src/main.rs`

### 三种循环结构

```rust
// 1. loop 无限循环
loop {
    count += 1;
    if count >= 3 { break; }
}

// 2. while 条件循环
while n > 0 { n -= 1; }

// 3. for in（迭代器驱动）
for i in 1..=5 { print!("{} ", i); }
```

### `for` 的多种迭代方式

```rust
for i in (1..=5).rev() { }       // 倒序：5,4,3,2,1
for i in (0..10).step_by(2) { }  // 步长：0,2,4,6,8

for v in &arr { }                // 引用方式（不转移所有权）
for (i, v) in arr.iter().enumerate() { }  // 带索引

for c in "你好Rust".chars() { }  // 遍历 Unicode 字符
for b in "hi".bytes() { }        // 遍历 UTF-8 字节
```

### 迭代器适配器链

```rust
let nums = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

let squares: Vec<i32> = nums.iter().map(|x| x * x).collect();
let evens: Vec<&i32> = nums.iter().filter(|x| *x % 2 == 0).collect();
let total: i32 = nums.iter().sum();

// 链式调用 —— Rust 最常用的惯用法
let result: i32 = nums.iter()
    .filter(|x| **x % 3 == 0)  // 3,6,9
    .map(|x| x * 10)            // 30,60,90
    .sum();                     // 180
```

- 迭代器是惰性的，直到 `collect`/`sum` 等消费方法调用才执行
- 链式调用是零成本抽象，编译后与手写循环一致
- 对比 Go：Go 没有内置的迭代器适配器

### `fold` 自定义累积

```rust
let product = nums.iter().fold(1, |acc, x| acc * x);
```

### 其他迭代器方法

```rust
nums.iter().take(3)                  // 取前 3 个
nums.iter().skip(7)                  // 跳过前 7 个
names.iter().zip(prices.iter())      // 拉链合并两个迭代器
(1..=3).chain(7..=9)                 // 拼接两个迭代器

let found = nums.iter().find(|&&x| x > 5);
let pos = nums.iter().position(|&x| x == 7);
nums.iter().all(|&x| x < 100)        // 全部满足？
nums.iter().any(|&x| x > 8)          // 存在满足？
```

### `while let` 模式

```rust
let mut stack = vec![1, 2, 3, 4, 5];
while let Some(top) = stack.pop() {
    print!("弹出 {} ", top);
}
```

- 持续循环直到模式不再匹配

---

## 第 7 章：向量 Vec

**文件：** `chapter07_vectors/src/main.rs`

### 创建 Vec

```rust
let mut v1: Vec<i32> = Vec::new();          // 空 Vec
let v2 = vec![1, 2, 3, 4, 5];               // vec! 宏（最常用）
let v3 = vec![0; 3];                         // [0, 0, 0]
let v4: Vec<i32> = (1..=5).map(|x| x * 2).collect(); // 从迭代器收集
let mut v5: Vec<i32> = Vec::with_capacity(100); // 预分配
```

### CRUD 与安全访问

```rust
let mut v = vec![10, 20, 30];
v.push(40);                    // 尾部追加
let last = v.pop();            // 尾部弹出（Option）
v.insert(1, 15);               // 中间插入（O(n)）
let removed = v.remove(0);     // 移除并返回（O(n)）

println!("v.get(0) = {:?}", v.get(0));   // Some(15)
println!("v.get(99) = {:?}", v.get(99)); // None（不 panic）
// println!("{}", v[99]); // 这行会 panic!
```

- `push`/`pop` 是 O(1)，`insert`/`remove` 是 O(n)
- `v.get(index)` 返回 `Option<&T>`，越界返回 `None`
- 对比 Go：Go 切片没有 `insert`/`remove`，需手写

### 所有权与 Vec

```rust
let mut names: Vec<String> = Vec::new();
let s = String::from("Alice");
names.push(s);                   // 所有权 move 进 Vec
// println!("{}", s); // 编译错误：s 已被移动
let owned = names.remove(0);     // 取出所有权
```

### 切片 `&[T]`

```rust
let big = vec![1, 2, 3, 4, 5, 6];
let slice: &[i32] = &big[1..4];  // [2, 3, 4]（零拷贝）

fn sum_slice(nums: &[i32]) -> i32 { nums.iter().sum() }

let arr = [1, 2, 3];
sum_slice(&arr);   // 数组自动退化为切片
sum_slice(&big);   // Vec 转切片
sum_slice(slice);  // 切片传切片
```

- `&[T]` 是借用的视图，不拥有数据，零拷贝
- 切片统一处理数组和 Vec，是函数参数的最佳实践类型

### 排序、去重、分割

```rust
v.sort();
v.sort_by(|a, b| b.cmp(a));   // 降序
v.reverse();
mixed.retain(|&x| x % 2 == 0); // 原地过滤
let tail = a.split_off(4);     // 从索引 4 分裂

let mut dup = vec![1, 2, 2, 3, 3, 3];
dup.sort();
dup.dedup();                   // 去重
```

### `chunks` 和 `windows`

```rust
let nums = [1, 2, 3, 4, 5];
for chunk in nums.chunks(2) { print!("{:?} ", chunk); } // [1,2] [3,4] [5]
for w in nums.windows(2) { print!("{:?} ", w); }        // [1,2] [2,3] [3,4] [4,5]
```

### 容量增长策略

```rust
let mut gv: Vec<i32> = Vec::new();
for i in 0..20 {
    gv.push(i);
    if gv.capacity() != prev_cap {
        // 输出：0 -> 4 -> 8 -> 16 -> 32
        prev_cap = gv.capacity();
    }
}
```

- Rust Vec 扩容策略约为 2 倍（0→4→8→16→32...），与 Go 切片类似

---

## 第 8 章：HashMap 与集合

**文件：** `chapter08_hashmaps/src/main.rs`

### 创建与插入

```rust
use std::collections::HashMap;

let mut scores: HashMap<String, i32> = HashMap::new();
scores.insert(String::from("Alice"), 95);
scores.insert(String::from("Bob"), 87);

// 从迭代器收集
let teams = vec![("红队", 10), ("蓝队", 25)];
let team_scores: HashMap<&str, i32> = teams.into_iter().collect();
```

### 安全读取（区分 None 和零值）

```rust
let alice = scores.get("Alice");   // Some(95)
let nobody = scores.get("Nobody"); // None —— 不是零值！

let score = scores.get("Alice").copied().unwrap_or(0);
println!("有 Alice? {}", scores.contains_key("Alice"));
```

- `get` 返回 `Option<&V>`，缺失键返回 `None`，不是零值
- 对比 Go：Go 的 `m[k]` 在键不存在时返回零值，无法区分不存在还是值恰好为零

### Entry API（Rust 最大亮点之一）

```rust
// 只在键不存在时插入
scores.entry(String::from("Cindy")).or_insert(60);
scores.entry(String::from("Alice")).or_insert(0); // 已存在，不覆盖

// 经典词频统计
let text = "go rust go java rust go python rust";
let mut word_count: HashMap<&str, i32> = HashMap::new();
for word in text.split_whitespace() {
    let count = word_count.entry(word).or_insert(0);
    *count += 1;  // count 是 &mut i32
}
```

- Entry API 是 Rust HashMap 最优雅的设计
- `entry(key).or_insert(val)` 在键不存在时插入，存在时不修改，返回 `&mut V`
- 对比 Go：Go 中需 `if v, ok := m[word]; ok { m[word] = v+1 } else { m[word] = 1 }`

### 删除操作

```rust
let removed = scores.remove("Cindy"); // 返回 Option<V>
if let Some((k, v)) = m2.remove_entry("k") { println!("{} = {}", k, v); }
m3.retain(|k, _| *k % 2 == 1); // 保留满足条件的
```

### BTreeMap（有序映射）

```rust
use std::collections::BTreeMap;
let mut sorted: BTreeMap<&str, i32> = BTreeMap::new();
sorted.insert("banana", 2);
sorted.insert("apple", 1);
sorted.insert("cherry", 3);
println!("BTreeMap: {:?}", sorted); // apple, banana, cherry（排序后）

// 范围查询
for (k, v) in sorted.range("apple".."cherry") {
    println!("{} = {}", k, v);
}
```

- 对比 Go：Go 标准库只有哈希表，有序映射需第三方库

### 更多集合

```rust
// HashSet —— 去重集合，支持集合运算
let union: HashSet<i32> = a.union(&b).cloned().collect();
let inter: HashSet<i32> = a.intersection(&b).cloned().collect();
let diff: HashSet<i32> = a.difference(&b).cloned().collect();

// VecDeque —— 双端队列
let mut dq = VecDeque::new();
dq.push_back(1);
dq.push_front(0);

// BinaryHeap —— 最大堆
let mut heap = BinaryHeap::new();
heap.push(3); heap.push(1); heap.push(5);
println!("堆顶（最大）: {:?}", heap.peek()); // Some(5)
```

---

## 第 9 章：函数与闭包

**文件：** `chapter09_functions/src/main.rs`

### 尾表达式返回值

```rust
fn add(a: i32, b: i32) -> i32 {
    a + b  // 无分号！尾表达式即为返回值
}
fn abs(x: i32) -> i32 {
    if x < 0 { return -x; }  // 提前返回用 return
    x  // 尾表达式
}
```

- Rust 是"面向表达式"的语言，代码块最后一个表达式（无分号）就是返回值
- 对比 Go：Go 必须写 `return`

### 块表达式

```rust
let y = {
    let x = 3;
    x + 1   // 尾表达式 = 块的值 = 4
};
// 如果 x + 1; 加了分号，块的值就是 ()
```

### 闭包语法

```rust
let add_one = |x: i32| -> i32 { x + 1 };
let square = |x| x * x;   // 参数类型待推断
let sq = square(4);       // 首次调用锁定类型为 i32
// let s = square("hi");  // 编译错误：类型已锁定为整数
```

- 闭包使用 `|参数| 表达式` 的轻量语法
- 一旦首次调用确定了类型就不能更改

### 三种捕获方式：Fn / FnMut / FnOnce

```rust
let mut count = 0;
let mut increment = || {  // FnMut：需要修改外部变量
    count += 1;
};
increment(); increment(); increment();

let name = String::from("Alice");
let consume = move || println!("{}", name); // FnOnce
```

- `Fn`：不可变借用，只读访问，可调用多次
- `FnMut`：可变借用，可修改捕获的变量，可调用多次
- `FnOnce`：取得所有权，只能调用一次
- `move` 关键字强制将捕获变量的所有权移入闭包——在线程中必用

### 闭包作为函数参数

```rust
fn apply<F: Fn(i32) -> i32>(f: F, x: i32) -> i32 {
    f(x)
}
println!("{}", apply(|x| x * 2, 10));
```

- 泛型 + trait 约束 = 静态分发（零开销抽象）

### 返回闭包与 `impl Fn`

```rust
fn make_adder(n: i32) -> impl Fn(i32) -> i32 {
    move |x| x + n  // move 捕获 n，因为闭包活得比 n 久
}
let add5 = make_adder(5);
println!("{}", add5(3)); // 8
```

### 函数指针 vs 闭包

```rust
fn double(x: i32) -> i32 { x * 2 }
let fns: [fn(i32) -> i32; 2] = [double, triple];
```

- 普通函数的类型是 `fn(i32) -> i32`（小写 `fn`）
- 闭包实现了 `Fn` trait

### 迭代器链式调用（Rust 惯用法）

```rust
let evens_sq_sum: i32 = nums.iter()
    .filter(|&&x| x % 2 == 0)
    .map(|&x| x * x)
    .sum();
```

### 发散函数（never type `!`）

```rust
fn forever() -> ! {
    loop {
        std::thread::sleep(Duration::from_secs(1));
    }
}
```

---

## 第 10 章：结构体

**文件：** `chapter10_structs/src/main.rs`

### 结构体定义与 derive 宏

```rust
#[derive(Debug, Clone, PartialEq)]
struct User {
    username: String,
    email: String,
    age: u8,
    active: bool,
}
```

- `#[derive(...)]` 让编译器自动实现指定的 trait
- `Debug`：`{:?}` 打印；`Clone`：深拷贝；`PartialEq`：`==` 比较
- 对比 Go：Go 需要手写这些

### impl 块：方法与关联函数

```rust
impl User {
    fn new(username: &str, email: &str, age: u8) -> Self { ... }
    fn greet(&self) -> String { ... }
    fn birthday(&mut self) { self.age += 1; }
    fn into_email(self) -> String { self.email }
}
```

- `&self`：不可变引用（读方法），`&mut self`：可变引用（写方法）
- `self`：取得所有权（消耗方法），调用后原实例不能再使用
- `new` 是没有 `self` 的关联函数（类似 Go 的构造函数）

### 结构体更新语法

```rust
let u2 = User {
    email: String::from("new@example.com"),
    ..u1.clone()  // 其余字段从 u1 克隆
};
```

### 元组结构体与 newtype 模式

```rust
struct Point(f64, f64);
struct Meters(f64);
struct Feet(f64);

let m = Meters(100.0);
let f = Feet(328.084);
// m + f  // 编译错误：不同单位不能混算！
```

- 元组结构体字段通过 `.0`、`.1` 访问
- Newtype 模式：用类型系统在编译期防止单位混淆

### 单元结构体

```rust
struct AlwaysEqual;
let _marker = AlwaysEqual;
println!("大小 = {} 字节", std::mem::size_of::<AlwaysEqual>()); // 0 字节
```

### 嵌套组合（组合代替继承）

```rust
struct Company {
    name: String,
    ceo: User,  // 组合：Company 拥有一个 User
}
```

- Rust 没有继承，复用通过组合实现

---

## 第 11 章：Trait 与泛型

**文件：** `chapter11_traits_generics/src/main.rs`

### Trait 定义（带默认实现）

```rust
trait Summary {
    fn summarize_author(&self) -> String;               // 必须实现
    fn summarize(&self) -> String {                     // 默认实现
        format!("（来自 {} 的内容...）", self.summarize_author())
    }
}
```

- Trait 类似其他语言的 interface
- 默认实现允许实现者选择覆盖或不覆盖
- 对比 Go：Go 接口没有默认实现

### 泛型函数与 trait 约束

```rust
fn notify<T: Summary>(item: &T) { println!("速报！{}", item.summarize()); }

// 多重约束
fn notify_both<T: Summary + Clone>(item: &T) { ... }

// where 子句
fn complex<T, U>(t: &T, u: &U) -> String
where T: Summary + Clone, U: Summary { ... }
```

- Rust 泛型通过**单态化**（monomorphization）编译，零运行时开销
- `+` 连接多个 trait bound
- `where` 子句在约束多时显著提高可读性

### Trait 对象 `dyn Trait`（动态分发）

```rust
fn print_summaries(items: &[Box<dyn Summary>]) {
    for item in items { println!("  - {}", item.summarize()); }
}

let feed: Vec<Box<dyn Summary>> = vec![
    Box::new(Article { ... }),
    Box::new(Weibo { ... }),
];
```

- `Box<dyn Trait>` 通过虚表（vtable）实现动态分发
- 泛型是静态分发（编译时确定），trait 对象是动态分发（运行时确定）

### 枚举作为代数数据类型

```rust
enum Shape {
    Circle { radius: f64 },
    Rectangle(f64, f64),
    Triangle(f64, f64, f64),
    Point,
}
impl Shape {
    fn area(&self) -> f64 {
        match self {
            Shape::Circle { radius } => PI * radius * radius,
            Shape::Rectangle(w, h) => w * h,
            Shape::Triangle(a, b, c) => { /* 海伦公式 */ },
            Shape::Point => 0.0,
        }
    }
}
```

### 运算符重载

```rust
impl std::ops::Add for Money {
    type Output = Money;
    fn add(self, rhs: Money) -> Money { Money(self.0 + rhs.0) }
}
```

### 关联类型

```rust
trait Iterator2 {
    type Item;  // 占位类型，实现时指定
    fn next(&mut self) -> Option<Self::Item>;
}
impl Iterator2 for Countdown {
    type Item = usize;
    fn next(&mut self) -> Option<usize> { ... }
}
```

### `From`/`Into` trait

```rust
impl From<i64> for Money {
    fn from(cents: i64) -> Self { Money(cents) }
}
let m: Money = 500.into();  // Into 自动可用
```

### 状态机模式

```rust
enum TrafficLight { Red, Yellow, Green }
impl TrafficLight {
    fn next(&self) -> TrafficLight {
        match self {
            TrafficLight::Red => TrafficLight::Green,
            TrafficLight::Green => TrafficLight::Yellow,
            TrafficLight::Yellow => TrafficLight::Red,
        }
    }
}
```

---

## 第 12 章：所有权（最重要）

**文件：** `chapter12_ownership/src/main.rs`

### 所有权三法则与移动语义

```rust
let s1 = String::from("hello");
let s2 = s1;       // 移动！不是浅拷贝！
// println!("{}", s1); // 编译错误：borrow of moved value
```

- `let s2 = s1` 是**移动**（move）而不是复制
- s1 的栈数据复制给了 s2，堆数据不动
- s1 立即被标记为"已移动"，编译器禁止继续使用
- 防止了双重释放（double free）

### Clone vs Copy

```rust
// Clone 深拷贝
let s3 = String::from("hello");
let s4 = s3.clone();  // 堆数据也复制

// Copy 类型：整数、浮点、bool、char 自动复制
let x = 42;
let y = x;  // 自动复制，x 仍可用
```

- Copy trait：按位拷贝，原变量仍有效（整数、bool、char 等栈类型）
- Clone trait：显式深拷贝，需调用 `.clone()`

### 函数参数与所有权

```rust
fn take_ownership(s: String) { }          // 所有权移入函数
fn borrow_it(s: &String) { }              // 借用，不拿所有权
fn give_back() -> String {
    String::from("新字符串")               // 所有权交还给调用者
}
```

### 借用规则

```rust
let mut data = String::from("hello");

let r1 = &data;
let r2 = &data;           // 多个不可变借用 ◯
println!("r1 = {}, r2 = {}", r1, r2);  // 最后使用点

let r3 = &mut data;       // 之后可以可变借用
r3.push_str(", world");
```

- 任意时刻：要么任意多个不可变引用，要么恰好一个可变引用
- 二者不能共存——这是 Rust 在编译期阻止数据竞争的核心机制

### 生命周期标注

```rust
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() { x } else { y }
}
struct Excerpt<'a> { part: &'a str }
```

- `'a` 不改变生命周期，只是描述引用之间的关系
- 返回值生命周期不超过 x 和 y 中较短的那个

### 悬垂引用被编译器消灭

```rust
// fn dangle() -> &String {    // 编译错误！
//     let s = String::from("x");
//     &s                       // 返回局部变量的引用
// }
```

### Rc（引用计数共享所有权）

```rust
use std::rc::Rc;
let shared = Rc::new(String::from("共享数据"));
let a = Rc::clone(&shared);
println!("{}", Rc::strong_count(&shared)); // 2
```

### 迭代的三种方式

```rust
let v = vec![1, 2, 3];
let sum: i32 = v.iter().sum();              // (a) 借用
let owned: Vec<i32> = v.into_iter().collect(); // (b) 消费
v.iter_mut().for_each(|x| *x += 1);         // (c) 可变借用
```

---

## 第 13 章：字符串

**文件：** `chapter13_strings/src/main.rs`

### `&str` vs `String`

```rust
let literal: &str = "我是字面量";   // 编译进二进制，零成本
let mut owned: String = String::new();
owned.push_str("我");
owned.push('是');

let s1 = String::from("直接创建");
let s2 = "从 &str 转换".to_string();
```

- `&str`：不可变引用，指向已有数据，零成本
- `String`：拥有所有权、可增长的堆分配字符串

### UTF-8 编码细节

```rust
let s = "你好Rust";
println!("{} 字节", s.len());               // 11 字节
println!("{} 个字符", s.chars().count());   // 7 个字符
// let c = s[0];  // 编译错误：不能按整数索引！

for (i, c) in s.char_indices() {            // 安全遍历
    println!("  字节 {} 处: {}", i, c);
}
```

- Rust 故意不提供 `s[i]` 整数索引（UTF-8 是变长编码）
- 要字符用 `.chars()`，要字节用 `.as_bytes()`

### 字符串拼接

```rust
let hello = String::from("Hello");
let world = String::from("世界");
let combined = hello + " " + &world;  // + 消耗掉 hello
// println!("{}", hello);  // 编译错误：hello 已被移入 +

let h2 = String::from("Hello");
let msg = format!("{} {}！", h2, world);  // 不消耗所有权
```

### 查找、替换、分割

```rust
let text = "Rust 很快，Rust 很安全";
println!("{}", text.contains("安全"));
println!("{}", text.find("Rust").unwrap());
println!("{}", text.replace("Rust", "Go"));

let csv = "name,age,city";
let fields: Vec<&str> = csv.split(',').collect();
```

### 解析字符串为数字

```rust
let n: i32 = "42".parse().unwrap();
let hex = i32::from_str_radix("ff", 16).unwrap();
match "abc".parse::<i32>() {
    Ok(v) => println!("成功 {}", v),
    Err(e) => println!("失败: {}", e),
}
```

---

## 第 14 章：错误处理

**文件：** `chapter14_errors/src/main.rs`

### `panic!` 与 `Result<T, E>`

```rust
fn crash_demo() { panic!("程序崩溃演示"); }

fn half_of(s: &str) -> Result<i32, Box<dyn std::error::Error>> {
    let n: i32 = s.parse()?;    // ?：Ok 继续，Err 提前返回
    if n % 2 == 0 { Ok(n / 2) } else { Err(Box::new(OddNumberError)) }
}
```

- `panic!`：不可恢复错误
- `Result<T, E>`：可恢复错误，`?` 运算符一行顶 Go 的 `if err != nil { return err }`

### 自定义错误类型

```rust
#[derive(Debug)]
enum AppError {
    Io(io::Error),
    Parse(ParseIntError),
}
impl std::error::Error for AppError { ... }
impl From<io::Error> for AppError { ... }

fn read_config(path: &str) -> Result<String, AppError> {
    let mut file = File::open(path)?;    // io::Error 自动 → AppError
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    Ok(content)
}
```

- 实现 `From` trait 后，`?` 运算符自动转换错误类型

### `Box<dyn Error>` 快速错误

```rust
fn quick() -> Result<(), Box<dyn Error>> {
    let _n: i32 = "x".parse()?;  // 不同错误类型自动装箱
    Ok(())
}
```

### 组合子

```rust
let r = "42".parse::<i32>()
    .map(|n| n * 2)
    .map_err(|e| e.to_string())
    .and_then(|n| if n > 50 { Ok(n) } else { Err("太小".into()) });
```

---

## 第 15 章：模块系统

**文件：** `chapter15_modules/src/main.rs` + 子模块

### `mod` 声明与文件查找

```rust
mod math;     // 查找 src/math.rs 或 src/math/mod.rs
mod network;  // 查找 src/network.rs 或 src/network/mod.rs
mod utils;    // 查找 src/utils.rs 或 src/utils/mod.rs
```

### `pub` 可见性控制

```rust
pub fn add(a: i32, b: i32) -> i32 { a + b }
fn _internal_help() { }   // 默认私有
```

- 一切默认私有，只有显式 `pub` 才能被外部访问
- 对比 Go：Go 基于首字母大小写

### 子模块嵌套

```rust
// network.rs
pub mod http;

// network/http.rs
#[derive(Debug)]
pub enum StatusCode { Ok = 200, NotFound = 404 }
```

- `super::` 访问父模块，`crate::` 从 crate 根开始

### `pub use` 重新导出

```rust
pub use internal::Helper;  // 提升到当前模块的公开 API
```

### 路径使用

```rust
println!("2 + 3 = {}", crate::math::add(2, 3));
use crate::network::http::StatusCode;
println!("{:?}", StatusCode::Ok);
```

---

## 第 16 章：并发编程

**文件：** `chapter16_concurrency/src/main.rs`

### 基本线程

```rust
let handle = thread::spawn(|| {
    for i in 1..=3 { println!("  [子线程] {}", i); }
    42                     // 线程可以返回值！
});
let result = handle.join().unwrap();
```

- 对比 Go：Go 的 `go` 关键字不返回值

### `move` 闭包

```rust
let data = vec![1, 2, 3];
let handle = thread::spawn(move || {   // move 必用！
    data.iter().sum::<i32>()
});
// println!("{:?}", data);  // 编译错误：data 已移入线程
```

### mpsc 通道

```rust
let (tx, rx) = mpsc::channel::<i32>();
let producer = thread::spawn(move || {
    for i in 1..=5 { tx.send(i * i).unwrap(); }
});
for val in rx { println!("收到 {}", val); }

// 多生产者
let tx2 = tx.clone();
thread::spawn(move || { tx.send("P1".into()).unwrap(); });
thread::spawn(move || { tx2.send("P2".into()).unwrap(); });
```

- 对比 Go：Rust mpsc 只能有一个接收端；`tx` 被 drop 时通道自动关闭

### `Arc<Mutex<T>>` 共享状态

```rust
let counter = Arc::new(Mutex::new(0));
let mut handles = vec![];
for _ in 0..5 {
    let counter = Arc::clone(&counter);
    handles.push(thread::spawn(move || {
        let mut num = counter.lock().unwrap();  // 加锁
        *num += 1;  // 自动解锁（MutexGuard drop）
    }));
}
```

- Rust 的 `Mutex<T>` 把数据包在锁内部——必须先 `.lock()` 获取 `MutexGuard` 才能访问
- `Arc<T>` 是线程安全的引用计数，`Arc::clone` 只增加引用计数
- 如果用 `Rc` 代替 `Arc`，编译器会报错——`Rc` 不是 `Send`

### Scoped Threads

```rust
let data = vec![10, 20, 30];
let doubled: Vec<i32> = std::thread::scope(|s| {
    let handles: Vec<_> = data.iter()
        .map(|&x| s.spawn(move || x * 2))
        .collect();
    handles.into_iter().map(|h| h.join().unwrap()).collect()
});
println!("data 还能用: {:?}", data);  // ✓
```

- `std::thread::scope` 允许线程安全地借用局部变量，不需要 `Arc`
- 作用域退出时自动 join 所有线程

### 其他并发原语

```rust
// 读写锁
let guard = data.read().unwrap();   // 读锁
let mut guard = data.write().unwrap(); // 写锁

// 原子类型
let hits = Arc::new(AtomicUsize::new(0));
hits.fetch_add(1, Ordering::Relaxed);

// 屏障
let barrier = Arc::new(Barrier::new(3));
b.wait();  // 等待 3 个线程都到达
```

### Go vs Rust 并发对照表

| Go | Rust |
|----|------|
| `go f(x)` | `thread::spawn(move \|\| f(x))` |
| `wg.Wait()` | `handle.join()` |
| `make(chan T)` | `mpsc::channel()` |
| `ch <- v` | `tx.send(v)` |
| `v := <-ch` | `rx.recv()` / `for v in rx` |
| `close(ch)` | `drop(tx)`（自动） |
| `sync.Mutex` | `Mutex<T>`（数据在锁内） |
| `sync.RWMutex` | `RwLock<T>` |
| `sync/atomic` | `AtomicUsize` / `AtomicBool` |
| `sync.WaitGroup` | `thread::scope` / JoinHandle 集合 |

---

# 第二篇：Web 框架（chapter17–19）

---

## 第 17 章：Poem Web 框架

**文件：** `chapter17_webapi_poem/src/main.rs`  
**依赖：** `poem = "3"`, `poem-openapi = "5"`, `tokio = "1"`

### 定义 OpenAPI 结构体

```rust
use poem_openapi::{payload::Json, OpenApi, OpenApiService};

struct Api;

#[OpenApi]
impl Api {
    #[oai(path = "/", method = "get")]
    async fn hello(&self) -> Json<&'static str> {
        Json("Hello, Poem!")
    }

    #[oai(path = "/user", method = "get")]
    async fn get_user(&self) -> Json<serde_json::Value> {
        Json(serde_json::json!({
            "id": 1, "name": "Alice", "email": "alice@example.com"
        }))
    }
}
```

### 集成 OpenAPI + Swagger UI + Scalar UI

```rust
let api_service = OpenApiService::new(Api, "Poem API", "1.0")
    .server("http://127.0.0.1:3000");

let ui = api_service.swagger_ui();
let scalar = api_service.scalar();
let spec = api_service.spec_endpoint();

let app = Route::new()
    .nest("/", api_service)
    .nest("/docs", ui)
    .nest("/scalar", scalar)
    .at("/spec", spec);
```

### 启动服务器

```rust
#[tokio::main]
async fn main() -> Result<(), std::io::Error> {
    Server::new(TcpListener::bind("127.0.0.1:3000"))
        .run(app)
        .await
}
```

---

## 第 18 章：Axum Web 框架

**文件：** `chapter18_webapi_axum/src/main.rs`  
**依赖：** `axum = "0.7"`, `utoipa = "5"`, `utoipa-swagger-ui = "8"`, `tokio = "1"`

### 定义带 OpenAPI 注解的数据模型

```rust
#[derive(Serialize, ToSchema)]
struct User {
    id: u64,
    name: String,
    email: String,
}
```

### 使用 utoipa 宏标注路由

```rust
#[utoipa::path(
    get,
    path = "/user",
    responses((status = 200, description = "User info", body = User))
)]
async fn get_user() -> Json<User> {
    Json(User { id: 1, name: "Alice".into(), email: "alice@example.com".into() })
}

#[utoipa::path(get, path = "/", responses((status = 200)))]
async fn hello() -> &'static str { "Hello, Axum!" }
```

### 构建路由与 Swagger UI

```rust
#[derive(OpenApi)]
#[openapi(paths(hello, get_user), components(schemas(User)))]
struct ApiDoc;

let app = Router::new()
    .route("/", get(hello))
    .route("/user", get(get_user))
    .merge(SwaggerUi::new("/docs").url("/openapi.json", ApiDoc::openapi()));

let listener = tokio::net::TcpListener::bind("127.0.0.1:3000").await.unwrap();
axum::serve(listener, app).await.unwrap();
```

---

## 第 19 章：Salvo Web 框架

**文件：** `chapter19_webapi_salvo/src/main.rs`  
**依赖：** `salvo = "0.74"`, `salvo-oapi = "0.74"`, `tokio = "1"`

```rust
#[derive(Serialize, ToSchema)]
struct User { id: u64, name: String, email: String }

#[endpoint]
async fn hello() -> &'static str { "Hello, Salvo!" }

#[endpoint(responses((status_code = 200, description = "User info", body = User)))]
async fn get_user() -> Json<User> {
    Json(User { id: 1, name: "Alice".into(), email: "alice@example.com".into() })
}

let router = Router::new()
    .get(hello)
    .push(Router::with_path("user").get(get_user));

let doc = salvo_oapi::OpenApi::new("Salvo API", "1.0").merge_router(&router);
let router = router
    .push(doc.into_router("/openapi.json"))
    .push(SwaggerUi::new("/openapi.json").into_router("/docs"));

let acceptor = TcpListener::new("127.0.0.1:3000").bind().await;
Server::new(acceptor).serve(router).await;
```

### 三大 Web 框架对比

| 特性 | Poem | Axum | Salvo |
|------|------|------|-------|
| API 定义 | `#[OpenApi] impl` 结构体 | 普通函数 + `#[utoipa::path]` | `#[endpoint]` 函数 |
| 路由模型 | `Route::new().nest()` | `Router::new().route()` | `Router::new().push()` |
| OpenAPI 集成 | 内置 | utoipa 第三方 | salvo-oapi 内置 |
| 文档 UI | Swagger + Scalar | Swagger | Swagger |
| 特点 | 类 Spring 控制器 | Tower 中间件生态 | 最小样板代码 |

---

# 第三篇：综合实战（chapter20–23）

---

## 第 20 章：Tauri 桌面应用

**文件：** `chapter20_tauri_app/src/main.rs`, `build.rs`  
**依赖：** `tauri = "2"`, `tauri-build = "2"`, `serde = "1"`

### Rust 后端

```rust
fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![greet])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}

#[tauri::command]
fn greet(name: &str) -> String {
    format!("你好, {}! 欢迎使用 Tauri App", name)
}
```

### 构建脚本

```rust
// build.rs
fn main() {
    tauri_build::build()
}
```

### 配置文件

```json
{
  "productName": "chapter20_tauri_app",
  "version": "0.1.0",
  "build": { "frontendDist": "dist" },
  "app": { "windows": [{ "title": "Tauri App Demo" }] }
}
```

Tauri 2 引入了基于 Capability 的权限系统，每个权限集指定哪些窗口可以使用哪些权限。

---

## 第 21 章：NAS 文件去重

**文件：** `chapter21_nas_dedup/src/main.rs`  
**依赖：** `sha2 = "0.10"`, `walkdir = "2"`, `rayon = "1"`, `clap = "4"`

### CLI 参数

```rust
#[derive(Parser)]
struct Args {
    #[arg(long)]
    dir_a: PathBuf,
    #[arg(long)]
    dir_b: PathBuf,
}
```

### SHA-256 哈希计算

```rust
fn file_hash(path: &PathBuf) -> Option<String> {
    let mut file = File::open(path).ok()?;
    let mut hasher = Sha256::new();
    let mut buf = [0u8; 64 * 1024];  // 64KB 缓冲区
    loop {
        let n = file.read(&mut buf).ok()?;
        if n == 0 { break; }
        hasher.update(&buf[..n]);
    }
    Some(format!("{:x}", hasher.finalize()))
}
```

### Rayon 并行哈希

```rust
let hashes: Vec<(PathBuf, Option<String>)> = all_files
    .par_iter()          // 自动并行
    .map(|f| (f.clone(), file_hash(f)))
    .collect();
```

### Entry API 分组

```rust
let mut groups: HashMap<String, Vec<PathBuf>> = HashMap::new();
for (path, hash) in hashes {
    if let Some(h) = hash {
        groups.entry(h).or_default().push(path);
    }
}
```

---

## 第 22 章：文件搜索工具

**文件：** `chapter22_everything_search/src/main.rs`  
**依赖：** `jwalk = "0.8"`, `clap = "4"`

### CLI 参数

```rust
#[derive(Parser)]
struct Args {
    #[arg(short, long)]
    query: String,
    #[arg(short, long, default_value = ".")]
    path: PathBuf,
    #[arg(short, long, default_value = "10")]
    max: usize,
}
```

### jwalk 并行目录遍历

```rust
for entry in WalkDir::new(&args.path)
    .parallelism(jwalk::Parallelism::RayonDefaultPool {
        busy_timeout: Duration::from_millis(10),
    })
    .into_iter()
    .filter_map(|e| e.ok())
{
    let name = entry.file_name().to_string_lossy().to_lowercase();
    if name.contains(&q) {
        println!("{}", entry.path().display());
        count += 1;
        if count >= args.max { break; }
    }
}
```

---

## 第 23 章：ORM 框架

**文件：** `chapter23_orm_framework/src/main.rs`  
**依赖：** `sqlx = "0.8"`, `tokio = "1"`, `chrono = "0.4"`, `serde = "1"`

### 定义模型

```rust
#[derive(Debug, Serialize, Deserialize, FromRow)]
struct User {
    id: i64,
    name: String,
    email: String,
    created_at: String,
}
```

### 连接池与建表

```rust
let pool = SqlitePoolOptions::new()
    .max_connections(5)
    .connect("sqlite://test.db?mode=memory")
    .await?;

sqlx::query(
    "CREATE TABLE IF NOT EXISTS users (
        id         INTEGER PRIMARY KEY AUTOINCREMENT,
        name       TEXT NOT NULL,
        email      TEXT NOT NULL,
        created_at TEXT DEFAULT (datetime('now'))
    )",
)
.execute(&pool)
.await?;
```

### 插入与查询

```rust
sqlx::query("INSERT INTO users (name, email) VALUES (?, ?)")
    .bind("Alice")
    .bind("alice@example.com")
    .execute(&pool)
    .await?;

let users: Vec<User> = sqlx::query_as("SELECT * FROM users")
    .fetch_all(&pool)
    .await?;
```

sqlx 的特点：SQL 优先、编译期检查（使用 `query!` 宏时）、通过 `FromRow` 派生宏自动映射，零运行时反射开销。

---

# 第四篇：核心概念深入（rust_book_01–06）

---

## rust_book_01_owner：所有权深入

**文件：** `main.rs`, `ref_demo.rs`, `first_world_demo.rs`

### Copy vs Move

```rust
let x = 5;
let y = x;
println!("x: {}", x); // ✅ Copy 类型：x 仍可用

let s1 = String::from("hello");
let s2 = s1.clone();
println!("s1: {}", s1); // ✅ 显式 clone 后 s1 仍可用
```

### 函数参数所有权转移

```rust
let s = String::from("hello");
takes_ownership(s);
// println!("{}", s); // ❌ 编译错误：所有权已转移

let x = 5;
makes_copy(x);
println!("{}", x); // ✅ i32 是 Copy 类型
```

### 不可变引用（借用）

```rust
let s1 = String::from("heloo");
let len = calculate_len(&s1);  // 只借不拿
println!("{}", s1);            // s1 仍然可用

fn calculate_len(s: &String) -> usize { s.len() }
```

### 可变引用

```rust
let mut s2 = String::from("hello");
change(&mut s2);
println!("{}", s2);

fn change(s: &mut String) { s.push_str(" world"); }
```

### 引用规则

```rust
let mut s = String::from("hello");
let r1 = &s;
let r2 = &s;                     // 多个不可变引用 ✓
println!("{} {}", r1, r2);       // 最后一次使用
let r3 = &mut s;                 // 之后可创建可变引用 ✓
```

### 字符串切片

```rust
fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();
    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' { return &s[0..i]; }
    }
    &s[..]
}
```

---

## rust_book_02_structure：结构体深入

**文件：** `user_demo.rs`, `area_demo.rs`

### 结构体定义与字段简写

```rust
struct User { username: String, email: String, sign_in_count: u64, active: bool }

fn build_user(email: String, username: String) -> User {
    User { email, username, active: true, sign_in_count: 1 }
}
```

### 四种面积计算方式

```rust
// 方式一：普通函数
fn area(width: u32, height: u32) -> u32 { width * height }

// 方式二：元组（不够可读）
fn areax(dimesions: (u32, u32)) -> u32 { dimesions.0 * dimesions.1 }

// 方式三：结构体（推荐）
#[derive(Debug)]
struct Rectangle { width: u32, height: u32 }

// 方式四：方法
impl Rectangle {
    fn area(&self) -> u32 { self.width * self.height }
    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}
```

### 关联函数

```rust
impl Rectangle {
    fn square(size: u32) -> Rectangle {
        Rectangle { width: size, height: size }
    }
}
let _rect2 = Rectangle::square(87); // :: 语法调用
```

---

## rust_book_03_enum：枚举深入

**文件：** `ipaddr_demo.rs`, `message_demo.rs`, `match_demo.rs`

### 枚举变体携带数据

```rust
enum IpAddrKind {
    V4(u8, u8, u8, u8),
    V6(String),
}
let localhost = IpAddrKind::V4(127, 0, 0, 1);
```

### 枚举的多种数据形态

```rust
enum Message {
    Quit,                       // 无数据
    Move { x: i32, y: i32 },   // 匿名结构体
    Write(String),              // 元组结构体
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn some_func() { println!("sdf") }
}
```

### `Option<T>` —— 消除 null

```rust
enum Option<T> { Some(T), None }

let num = Some(5);              // Option<i32>
let abs_num: Option<i32> = None; // 需显式类型标注
```

### `match` 模式匹配

```rust
fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        Some(i) => Some(i + 1),
        _ => None,  // 通配符
    }
}
let six = plus_one(Some(5));     // Some(6)
let none = plus_one(None);       // None
```

---

## rust_book_04_generic：泛型深入

**文件：** `generic_demo.rs`

### 泛型函数

```rust
fn get_largest<T: PartialOrd + Copy>(num_lst: Vec<T>) -> T {
    let mut largest = num_lst[0];
    for number in num_lst {
        if number > largest { largest = number }
    }
    largest
}
```

### 泛型结构体

```rust
struct Pnt<T, K> { x: T, y: K }

let p1 = Pnt { x: 5, y: 10 };       // Pnt<i32, i32>
let p2 = Pnt { x: 5.0, y: 10.0 };   // Pnt<f64, f64>
let p3 = Pnt { x: 5, y: 10.0 };     // Pnt<i32, f64>
```

### 条件方法实现

```rust
// 所有 Pnt<T> 都有 x() 方法
impl<U> Pnt<U> { fn x(&self) -> &U { &self.x } }

// 只有 Pnt<f64> 有 y() 方法
impl Pnt<f64> { fn y(&self) -> &f64 { &self.y } }
```

---

## rust_book_05_trait：Trait 深入

**文件：** `trait_demo.rs`, `pair_demo.rs`

### Trait 定义与默认实现

```rust
pub trait Summary {
    fn summarize(&self) -> String {
        String::from("Read more ...")
    }
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}, {}", self.content, self.username)
    }
}
```

### Trait 作为参数

```rust
// 语法糖：impl Trait
fn nofify(item: &impl Summary) {
    println!("breaking news !:{}", item.summarize())
}

// 泛型 + 多约束
fn notify<T: Summary + Display>(item1: &T, item2: &T) { ... }

// where 子句
fn some_func<T, K>(t: &T, k: &K) -> i32
where T: Display + Clone, K: Clone + Debug { 1 }
```

### 返回 impl Trait

```rust
fn ret_tweet_summary() -> impl Summary {
    Tweet { username: String::from("horse_ebook"), content: String::from("..."), reply: false, retweet: false }
}
```

### 条件方法实现

```rust
struct Pair<T> { x: T, y: T }

impl<T: Display + PartialOrd> Pair<T> {
    fn cmp_display(&self) {
        if self.x >= self.y {
            println!("largest: x{}", self.x);
        } else {
            println!("largest: y{}", self.y);
        }
    }
}
```

---

## rust_book_06_lifetime：生命周期深入

**文件：** `lifetime_demo.rs`, `struct_lifetime.rs`, `static_lifetime.rs`, `main.rs`

### 函数生命周期标注

```rust
// 返回值生命周期 = 两个参数中较短的那个
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() { x } else { y }
}

// 返回值只与 x 绑定，不受 y 影响
fn longestX<'a>(x: &'a str, y: &str) -> &'a str { x }
```

### 生命周期在作用域中的表现

```rust
pub fn func2() {
    let str1 = String::from("adb");
    let result;
    {
        let str2 = String::from("xyz");
        result = longestX(str1.as_str(), str2.as_str()); // 引用 str1
    } // str2 销毁，但 result 引用 str1，安全
    println!("the longest is {}", result);
}
```

### 结构体生命周期

```rust
struct ImportantExcerpt<'a> { part: &'a str }

impl<'a> ImportantExcerpt<'a> {
    fn return_part(&self, announcement: &str) -> &str {
        println!("attention please:{}", announcement);
        self.part
    }
}
```

### 静态生命周期 `'static`

```rust
let s: &'static str = "i have a plan";  // 整个程序运行期间有效
```

### 综合示例：泛型 + Trait + 生命周期

```rust
fn longest_with_an_announcement<'a, T>(x: &'a str, y: &'a str, ann: T) -> &'a str
where T: Display,
{
    println!("announcement!!{}", ann);
    if x.len() > y.len() { x } else { y }
}
```

---

# 学习路线建议

```
第 1 阶段：基础入门
  chapter01 → chapter02 → chapter03 → chapter04
  chapter05 → chapter06

第 2 阶段：数据结构
  chapter07 → chapter08 → chapter10 → chapter13

第 3 阶段：核心概念（搭配 rust_book 系列）
  chapter12 + rust_book_01_owner  (所有权)
  chapter09 + rust_book_04_generic (泛型)
  chapter11 + rust_book_05_trait   (Trait)
  chapter14 + rust_book_06_lifetime (生命周期)

第 4 阶段：组织与并发
  chapter15 → chapter16

第 5 阶段：Web 开发（任选一个框架）
  chapter17（Poem）/ chapter18（Axum）/ chapter19（Salvo）

第 6 阶段：综合实战
  chapter21 → chapter22 → chapter23 → chapter20
```

---

# Rust 与 Go 关键差异速查表

| 特性 | Rust | Go |
|------|------|----|
| **变量默认** | 不可变（`let`） | 可变（`var` / `:=`） |
| **空值** | `Option<T>`（无 null） | `nil`（指针/切片/map 零值） |
| **异常处理** | `Result<T, E>` + `?` | `error` 多返回值 |
| **内存管理** | 所有权/借用（编译期） | 垃圾回收（runtime） |
| **循环** | `loop` / `while` / `for in` | 仅有 `for` |
| **模式匹配** | `match`（穷尽性检查） | 无（switch 有限） |
| **运算符重载** | 支持（`std::ops`） | 不支持 |
| **三目运算符** | 无（if-else 表达式） | 无 |
| **自增/自减** | 无（`i += 1`） | 有 `i++` / `i--` |
| **整数溢出** | debug panic / release 回绕 | 始终回绕 |
| **数据竞争防御** | 编译期借用规则 | 运行时 `-race` 检测 |
| **泛型** | 单态化（零成本） | 接口实现（运行时派发） |
| **枚举** | 代数数据类型 | iota 常量 |
| **集合** | Vec + &[T] 分工明确 | 切片作为一等公民 |
| **HashMap API** | Entry API 极强大 | 基本 CRUD |
