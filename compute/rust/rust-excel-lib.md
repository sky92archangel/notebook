

# Rust Excel库选型速览

[TOC]

| crate                | 读写能力  | 特点                                                         | 适用场景                                 |
| -------------------- | --------- | ------------------------------------------------------------ | ---------------------------------------- |
| **calamine**         | ✅只读     | 纯Rust，支持`xls/xlsx/xlsm/xlsb/ods`，支持serde反序列化，**大文件友好**，不依赖Office | 读取解析、数据导入、批量读表             |
| **rust_xlsxwriter**  | ✅只写     | 原python xlsxwriter移植，样式/公式/图表能力很强，API成熟     | **新建导出xlsx报表**（不能读取已有文件） |
| **excelize-rs**      | ✅读写     | Go excelize的Rust移植，支持公式计算、图表、图片、条件格式    | 需要**修改已有xlsx**、复杂报表           |
| **umya_spreadsheet** | ✅读写     | 纯Rust，完整xlsx读写，支持lazy懒加载                         | 中等复杂度xlsx读写                       |
| **excelstream**      | ✅流式读写 | 低内存流式处理，适合GB级超大Excel                            | 超大数据量，内存受限场景                 |

> 生产最常用组合：**calamine读 + rust_xlsxwriter写**，各司其职，稳定性最好。

------

## 1. calamine 读取Excel（只读）

### Cargo.toml

```
[dependencies]
calamine = "0.22"
```

### 基础读取示例

```
use calamine::{open_workbook, Xlsx, Reader, DataType};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 打开xlsx文件
    let mut wb: Xlsx<_> = open_workbook("data.xlsx")?;
    // 获取Sheet1的单元格区域
    let range = wb.worksheet_range("Sheet1")
        .ok_or("找不到Sheet1")??;

    // 遍历每一行
    for (row_idx, row) in range.rows().enumerate() {
        println!("行{}: ", row_idx);
        for cell in row {
            let val = match cell {
                DataType::String(s) => s.clone(),
                DataType::Float(n) => n.to_string(),
                DataType::Int(i) => i.to_string(),
                DataType::Bool(b) => b.to_string(),
                DataType::Empty => "".to_string(),
                _ => "[其他类型]".to_string(),
            };
            print!("{} | ", val);
        }
        println!();
    }
    Ok(())
}
```

### Serde自动反序列化（非常好用）

```
calamine = { version = "0.22", features = ["serde"] }
serde = { version = "1.0", features = ["derive"] }
use calamine::{open_workbook, Xlsx, RangeDeserializerBuilder};
use serde::Deserialize;

#[derive(Debug, Deserialize)]
struct Record {
    name: String,
    age: i32,
    score: f64,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut wb: Xlsx<_> = open_workbook("data.xlsx")?;
    let range = wb.worksheet_range("Sheet1").ok_or("sheet not found")??;
    // 第一行作为表头
    let mut iter = RangeDeserializerBuilder::new().from_range(&range)?;

    for row in iter {
        let rec: Record = row?;
        println!("{:?}", rec);
    }
    Ok(())
}
```

------

## 2. rust_xlsxwriter 写入Excel（只写，新建文件）

### Cargo.toml

```
[dependencies]
rust_xlsxwriter = "0.99"
```

### 写入示例（支持样式、公式）

```
use rust_xlsxwriter::{Workbook, Format, FormatAlign, Formula};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut workbook = Workbook::new();
    let sheet = workbook.add_worksheet();
    sheet.set_name("销售表")?;

    // 定义加粗居中格式
    let header_style = Format::new()
        .set_bold()
        .set_align(FormatAlign::Center);

    // 写入表头
    sheet.write_with_format(0,0,"姓名", &header_style)?;
    sheet.write_with_format(0,1,"金额", &header_style)?;

    // 写入数据
    sheet.write(1,0,"张三")?;
    sheet.write(1,1,1000)?;
    sheet.write(2,0,"李四")?;
    sheet.write(2,1,2000)?;

    // 写入公式
    sheet.write(3,1,Formula::new("=SUM(B2:B3)"))?;

    // 设置列宽
    sheet.set_column_width(0, 15)?;
    sheet.set_column_width(1, 12)?;

    workbook.save("output.xlsx")?;
    Ok(())
}
```

> ⚠️ 重要：rust_xlsxwriter**不能打开已有xlsx修改**，只能新建。

------

## 3. excelize-rs 读写修改已有xlsx

适合需要**加载原有文件、修改单元格/图片/公式**场景

```
[dependencies]
excelize-rs = "0.1.9"
use excelize_rs::Excelize;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut f = Excelize::new_file();
    // 打开已有文件
    f.open_file("source.xlsx")?;
    // 修改单元格
    f.set_cell_value("Sheet1", "A1", "修改后的内容")?;
    f.save_as("modified.xlsx")?;
    Ok(())
}
```

# 选型建议

1. **只读取数据，批量导入** → `calamine`（首选，纯rust、支持xlsb，serde自动映射结构体）
2. **导出报表、生成新xlsx，需要样式/图表/公式** → `rust_xlsxwriter`（API友好，文档完善）
3. **读取旧文件，修改再保存** → `excelize-rs`
4. **超大文件、低内存流式处理** → `excelstream`

# 常见坑

1. calamine 只可读，不能写；rust_xlsxwriter只可写，不能读；二者搭配是主流方案
2. xls（旧版二进制格式）calamine支持，rust_xlsxwriter不支持xls，只支持xlsx
3. 日期：calamine读出的日期是浮点数，需要手动转换；rust_xlsxwriter内置日期格式化
4. 中文路径：Windows下Rust标准库正常支持，但注意文件编码

如果你需要，我可以给你：

- 完整工程：calamine读 → 业务处理 → rust_xlsxwriter输出报表
- 或者 带serde + 错误处理的完整生产模板。







