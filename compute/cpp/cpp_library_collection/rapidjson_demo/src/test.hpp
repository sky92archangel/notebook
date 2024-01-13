
#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string.h>

#include <Eigen/Dense>
using namespace rapidjson;

int DEMO01()
{
    std::cout << "\n\n\n"
              << std::endl;

    // 1. 把 JSON 解析至 DOM。
    const char *json = "{\"project\":\"rapidjson\",\"stars\":10}";
    printf("%s \n", json);

    Document jsonDoc;
    jsonDoc.Parse(json);

    // 2. 利用 DOM 作出修改。
    Value &s = jsonDoc["stars"];
    std::cout << "stars:" << s.GetInt() << std::endl;
    std::cout << "type:" << s.GetType() << std::endl;
    std::cout << "project-type:" << jsonDoc["project"].GetType() << std::endl;
    s.SetInt(s.GetInt() + 1);

    // 3. 把 DOM 转换（stringify）成 JSON。
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    // Output {"project":"rapidjson","stars":11}

    printf("%s \n", std::string(buffer.GetString()).c_str()); // 直接采用std::string的构造函数，返回一个临时变

    std::cout << "buffer:" << buffer.GetString() << std::endl;

    return 0;
}

// #include "memory.h"
// #include <ctime>
// #include <stdio.h>
int DEMO02()
{
    Document jsonDoc;
    Document::AllocatorType &allocator = jsonDoc.GetAllocator();
    jsonDoc.SetObject();

    // 主对象
    Value value(kObjectType);
    value.AddMember("flag", 0, allocator);
    value.AddMember("msg", u8"操作成功", allocator);

    // result对象
    Value result(kObjectType);
    // 添加result的基本信息
    result.AddMember("name", u8"(匿名)", allocator);
    result.AddMember("right_query", true, allocator);

    // 创建一个array对象，用于存储t信息
    Value arraych(kArrayType);
    struct chunnels
    {
        int chunnel;
        std::string username;
        std::string telphone;
    };

    for (int i = 0; i < 5; i++)
    {
        chunnels ch;
        ch.chunnel = 0;
        ch.username = u8"黎明";
        ch.telphone = "113";

        Value chu(kObjectType);
        Value v0;
        v0.SetInt(ch.chunnel); // 数值型这样写

        Value v1(ch.username.c_str(), allocator); // 字符串这样写就不会出现/u0000的问题了
        Value v2(ch.telphone.c_str(), allocator);

        chu.AddMember("chunnel", v0, allocator);
        chu.AddMember("username", v1, allocator);
        chu.AddMember("telphone", v2, allocator);

        // chu.AddMember("第三种写法", "6666", allocator); // 直接内容的话，不需要转

        arraych.PushBack(chu, allocator);
    }

    // 将集合添加到result对象中
    result.AddMember("chunnels", arraych, allocator);
    // 将result对象加入到主对象
    value.AddMember("result", result, allocator);

    // 转为string

    StringBuffer str;
    Writer<StringBuffer> writer(str);
    value.Accept(writer);
    std::string strJson = str.GetString();
    std::cout << strJson << std::endl;

    return 0;
}

int DEMO03()
{

    //  std::cout << "json Value的新建及key的访问" << std::endl;
    //  std::cout<<"json Value 的新建和key的访问"<<std::endl;

    Document jsonDoc;                                            // 生成一个dom元素Document
    Document::AllocatorType &allocator = jsonDoc.GetAllocator(); // 获取分配器
    jsonDoc.SetObject();                                         // 将当前的Document设置为一个object，也就是说，整个Document是一个Object类型的dom元素

    // 新建Value对象1(object类型)
    Value value1(kObjectType);
    value1.AddMember("name", "语文", allocator);           // string型(给字段赋值，key必须为string型下同)
    value1.AddMember("score", 80, allocator);              // 整型
    value1.AddMember("right", true, allocator);            // 整型
    value1.AddMember("percent", 12.3456789123, allocator); // double型

    // 此时访问key是可以的
    if (value1.HasMember("name")) // 判断是否存在该key
    {
        if (value1["name"].IsString()) // 再判断类型是否正确
        {
            std::cout << "value1:name:" << value1["name"].GetString() << std::endl;
        }
        std::cout << "value1:score:" << value1["score"].GetInt() << std::endl; // 直接这样写有风险
    }

    // 新建Value对象(数组类型)
    Value value2(kArrayType);
    value2.PushBack(1, allocator);
    value2.PushBack(2, allocator);
    value2.PushBack(3, allocator);
    std::cout << "value:size()数组中元素个数:" << value2.Size() << std::endl;

    // 合并一个整体
    Value value3(kObjectType);
    value3.AddMember("name", "xiaoming", allocator);
    value3.AddMember("age", 18, allocator);
    value3.AddMember("value1", value1, allocator); // 整个value1作为key的值
    value3.AddMember("value2", value2, allocator); // 整个value2作为key的值

    // 转为string
    StringBuffer str;
    Writer<StringBuffer> writer(str);
    value3.Accept(writer);
    std::string strJson = str.GetString();
    std::cout << "value3:" << strJson.c_str() << std::endl;

    return 0;
}