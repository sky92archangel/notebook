#pragma once

#include <iostream>
#include <fstream>

#include <json/json.h>
#include <json/value.h>

namespace jsoncpp_handler
{

    bool JsonTypeLegal(Json::Value &v, Json::ValueType type)
    {
        switch (type)
        {
        case Json::ValueType::intValue:
        case Json::ValueType::uintValue:
        {
            if (v.isInt() || v.isUInt() || v.isInt64() || v.isUInt64())
            {
                return true;
            }
            break;
        }
        case Json::ValueType::realValue:
        {
            if (v.isDouble())
            {
                return true;
            }
            break;
        }
        case Json::ValueType::stringValue:
        {
            if (v.isString())
            {
                return true;
            }
            break;
        }
        case Json::ValueType::booleanValue:
        {
            if (v.isBool())
            {
                return true;
            }
            break;
        }
        case Json::ValueType::arrayValue:
        {
            if (v.isArray())
            {
                return true;
            }
            break;
        }
        case Json::ValueType::objectValue:
        {
            if (v.isObject())
            {
                return true;
            }
            break;
        }
        default:
            break;
        }

        return false;
    }

 

    class json_excption : public std::runtime_error
    {
    public:
        json_excption(const char *msg) : std::runtime_error(msg) {}

        json_excption() = default;
        ~json_excption() = default;
    };




    [[noreturn]] void raise(const char *msg)
    {
        throw json_excption(msg);
    }

 
#define JSON_OBJECT_VERFY(json, type)                                        \
    [&](Json::Value &v)                                                      \
    {                                                                        \
        std::ostringstream strOut;                                           \
        if (!v || v.isNull())                                                \
        {                                                                    \
            strOut << "Json Object Non_Exist:" << #json << std::endl;        \
            raise(strOut.str().c_str());                                     \
        }                                                                    \
        else if (!JsonTypeLegal(v, type))                                    \
        {                                                                    \
            strOut << "Json Object type is not legal" << #json << std::endl; \
            raise(strOut.str().c_str());                                     \
        }                                                                    \
        return v;                                                            \
    }(json)

}
