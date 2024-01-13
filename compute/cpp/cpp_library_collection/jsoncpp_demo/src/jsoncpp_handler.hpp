#pragma once

#include <iostream>
#include <fstream>

#include <json/json.h>
#include <json/value.h>

namespace jsoncpp_hangler
{

    // 将json文件文本 读取 并 转化为jsonvalue这个中间对象格式
    bool FileToValue(const std::string &path, Json::Value &value)
    {
        std::ifstream ifs;
        ifs.open(path);

        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;

        JSONCPP_STRING errs;
        if (!Json::parseFromStream(builder, ifs, &value, &errs))
        {
            std::cout << errs << std::endl;
            ifs.close();
            return false;
        }
        ifs.close();
        return true;
    }

    //将字符串转化为 jsonvalue这个中间对象格式
    bool StringToValue(const std::string jsonStr, Json::Value &value)
    {
        const auto length = static_cast<int>(jsonStr.length());
        Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

        JSONCPP_STRING errs;
        if (!reader->parse(jsonStr.c_str(), jsonStr.c_str() + length, &value, &errs))
        {
            std::cout << errs << std::endl;
            return false;
        }
        return true;
    }

    ///将jsonvalue这个中间对象的数据保存为本地json文件
    bool ValueToFile(const std::string path, Json::Value &value)
    {
        std::ofstream ofs(path.c_str());
        if (!ofs)
        {
            ofs.close();
            return false;
        }

        Json::StreamWriterBuilder builder;
        const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

        writer->write(value, &ofs);
        ofs.close();
        return true;
    }

    ///将jsonvalue这个中间对象转化为json字符串
    bool ValueToString( std::string &jsonStr, Json::Value &value)
    {
        Json::StreamWriterBuilder builder;
        // jsonStr =  static_cast<std::string>(Json::writeString(builder, value));
        jsonStr = Json::writeString(builder, value);
        return true;
    }

}