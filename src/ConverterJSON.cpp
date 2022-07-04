#include "ConverterJSON.h"

std::vector<std::string> ConverterJSON::getTextDocument() {
    nlohmann::json JSONservant;
    inputFile.open("config.json");
    std::vector<std::string>wordsInFilesVector;
    if(inputFile.is_open()) {

        inputFile >> JSONservant;

        inputFile.close();
        wordsInFilesVector.resize(JSONservant["files"].size());
        for (int i = 0; i < JSONservant["files"].size(); ++i) {
            if(JSONservant["files"][i].empty())
            {
                std::cerr<<"file pass is empty\n";
                continue;
            }
            inputFile.open(JSONservant["files"][i]);
            if (inputFile.is_open()) {
                if (i < wordsInFilesVector.size()) {
                    std::string temps( (std::istreambuf_iterator<char>(inputFile)),
                                       (std::istreambuf_iterator<char>()));

                    wordsInFilesVector[i] = temps;

                }
                inputFile.close();
            } else {
                std::cerr<<"file couldn't open\n";
                continue;
            }
        }
    }
    return wordsInFilesVector;
}

int ConverterJSON::GetResponsesLimit() {
    nlohmann::json JSONservant;
    inputFile.open("config.json");
    if(inputFile.is_open())
    {
        inputFile >> JSONservant;
        inputFile.close();
        return JSONservant["config"]["max_responses"];
    }
    return 0;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    nlohmann::json JSONservant;
    inputFile.open("requests.json");
    if(inputFile.is_open())
    {
        inputFile>>JSONservant;
        inputFile.close();
        std::vector<std::string> requests(JSONservant["requests"].size());

            for (int i = 0; i < requests.size(); ++i) {
                requests[i] = JSONservant["requests"][i];
            }


        return requests;
    }

    return std::vector<std::string>();
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers) {
    nlohmann::json JSONservant;
    std::vector<std::string> request = GetRequests();

    for(int i = 0; i<answers.size(); ++i) {

        if (answers[i].empty())
        {
            JSONservant["Answers"][request[i]]["result"] = false;
        }
        else
        {
            JSONservant["Answers"][request[i]]["result"] = true;
            nlohmann::json jsonAnswers;
            for(auto a: answers[i]) {
                nlohmann::json JSONrank;
                JSONrank["docid:"] = a.doc_id;
                JSONrank["rank:"] = a.rank;
                jsonAnswers.push_back(JSONrank);
            }
            JSONservant["Answers"][request[i]]["relevance"] = jsonAnswers;
        }
    }

    outputFile.open("answers.json");
    if (outputFile.is_open()) {
        outputFile << JSONservant;
        outputFile.close();
    }
    else
    {
        std::ofstream newAnswersFile("answers.json");
        newAnswersFile<< JSONservant;
        newAnswersFile.close();
    }
}

void ConverterJSON::checkConfigs() {
    std::ifstream checking;
    checking.open("config.json");
    if(checking.is_open())
    {
        nlohmann::json configCheck;
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
            throw CONFIGMissingExeption("config file is empty");
        }

    }
    else
    {
        checking.close();
        throw CONFIGMissingExeption("config file is missing");
    }
}

void ConverterJSON::checkRequests() {
    std::ifstream file;
    file.open("requests.json");

    if(file.is_open())
    {
        nlohmann::json requestsCheck;
        file>>requestsCheck;
        if(requestsCheck["requests"].empty())
        {
            file.close();
            throw REQUESTSMissingExeption("Request.json have not requests\n");
        }
        else
        {
            std::cout<<"In requests.json have fallowing requests:\n";
            for(std::string rec : requestsCheck["requests"])
            {
                std::cout<<rec<<std::endl;
            }
            file.close();
        }
    }
    else
    {
        file.close();
        throw REQUESTSMissingExeption("File requests.json is missing\n");
    }
}
