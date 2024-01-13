#pragma once

#include <iostream>
#include <string>
#include <json/json.h>

namespace jsoncpp_handler
{

    int Run()
    {

        const char *buffer = "{\"name\":\"zhou sky\",  \"age\":130, \"score\":[ {\"data\" :15,\"dataname\":\"chs\"},{\"data\":48},{\"data\":99} ]  }";
        // const char *buffer = "{\"name\":\"zhousky\",  \"age\":130,  \"agex\":130 ";

        Json::Reader reader;
        Json::Value root;
        std::cout << "  start" << std::endl;
        bool result = reader.parse(buffer, root);
        if (!result)
        {
            perror("parse error");
            // return -1;
        }
        std::cout << root.toStyledString() << std::endl;

        //---------------
        Json::Value nameValue = root.get("name", nameValue);
        std::string name = nameValue.asString();
        std::cout << "name:" << nameValue << std::endl;
        //---------------
        Json::Value ageValue = root.get("age", ageValue);
        int age = ageValue.asInt();
        std::cout << "age:" << ageValue << std::endl;
        //---------------
        Json ::Value scoreValue;
        scoreValue = root.get("score", scoreValue);
        bool isarray = scoreValue.isArray();
        if (isarray)
        {
            std::cout << "score is array" << std::endl;
            int size = scoreValue.size();
            std::cout << "size:" << size << std::endl;
            for (int i = 0; i < size; i++)
            {
                Json ::Value itemData;
                itemData = scoreValue[i].get("data", itemData);
                int data = itemData.asInt();
                std::cout << "data" << i << ":" << data << std::endl;
            }
        }
        else
        {
            std::cout << "score is not array" << std::endl;
        }

        return 0;
    }

}