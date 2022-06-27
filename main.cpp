#include <iostream>
#include <algorithm>
#include "gtest/gtest.h"
#include "JSONMissingExeption.h"
#include "InvertedIndex.h"
#include "ConverterJSON.h"




#ifndef  TESTS
using namespace  nlohmann;


void checkConfigs()
{
    std::ifstream checking;
    checking.open("config.json");
    if(checking.is_open())
    {
        json configCheck;
        checking>>configCheck;

        if(!configCheck["config"].empty())
        {
            std::cout<<configCheck["config"]["name"]<<std::endl;
            std::cout<<configCheck["config"]["version"]<<std::endl;
            checking.close();
        }
        else
        {
            checking.close();
            throw JSONMissingExeption("config file is empty");
        }
    }
    else
    {
        checking.close();
        throw JSONMissingExeption("config file is missing");
    }
}

int main() {

    try {
        checkConfigs();
    }
    catch(JSONMissingExeption ex)
    {
        std::cerr<<"Error: "<<ex.what()<<std::endl;
        return 1;
    }

    return 0;
}

#endif