#include "InvertedIndex.h"
#include "ConverterJSON.h"
#include "SearchServer.h"

#ifndef  TESTS
using namespace  nlohmann;

void showComands();



int main() {
    ConverterJSON j;

  /* try {

        j.checkConfigs();
        j.checkRequests();

    }
    catch(CONFIGMissingExeption ex)
    {
        std::cout<<"Error: "<<ex.what();
        return 1;
    }
    catch (REQUESTSMissingExeption ex)
    {
        std::cout<<"Error: "<<ex.what();
        if(j.getIsEmpty())
        {
            while (true) {

                std::cout << "Would you want to create this file?(y/n)\n";
                std::string answer;
                std::cin >> answer;
                if (answer == "y") {
                    std::ofstream file("requests.json");
                    json requests;
                    requests["requests"] = {};
                    file << requests;
                    file.close();
                    std::cout << "file created!\n";
                    break;
                } else if (answer == "n") {
                    break;
                } else {
                    std::cout << "wrong comand!\n";
                }
            }
        }
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
    }*/
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