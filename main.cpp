#include <iostream>
#include <algorithm>
#include "JSONMissingExeption.h"
#include "InvertedIndex.h"
#include "ConverterJSON.h"
#include "SearchServer.h"




#ifndef  TESTS
using namespace  nlohmann;

void showComands();

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
            std::cout<<"input ? for help\n";
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

    bool isWork = true;
    std::string comand;

    while(isWork)
    {
        std::cout<<"input command: ";
        std::cin>>comand;
        if(comand == "?")
        {
            showComands();
        }
        else if(comand == "q")
        {
            std::cout<<"finish\n";
            isWork = false;
        }
        else if(comand == "s")
        {
           std::cout<<"start searching\n";
           ConverterJSON converter;
           InvertedIndex idx;
           idx.UpdateDocumentBase(converter.getTextDocument());
           SearchServer srv(idx);

           converter.putAnswers(srv.search(converter.GetRequests()));

           std::cout<<"Search completed. Check answers.json\n";
        }
        else
        {
            std::cout<<"Wrong command\n";
        }
    }

    return 0;
}

void showComands()
{
    std::cout<<"? - comand list\n";
    //std::cout<<"r - show requests\n";
    //std::cout<<"rl - show responsesLimit\n";
    std::cout<<"s - make search\n";
    std::cout<<"q - exit from app\n";
}



#endif