#include "ConverterJSON.h"

std::vector<std::string> ConverterJSON::getTextDocument() {
    nlohmann::json JSONservant;
    inputFile.open("config.json");
    std::vector<std::string>wordsInFilesVector;
    if(inputFile.is_open()) {
        std::cout << "get worlds!\n";
        inputFile >> JSONservant;
        std::cout << "world getted!\n";
        inputFile.close();
        wordsInFilesVector.resize(JSONservant["files"].size());
        for (int i = 0; i < JSONservant["files"].size(); ++i) {
            if(JSONservant["files"][i].empty()) continue;
            inputFile.open(JSONservant["files"][i]);
            if (inputFile.is_open()) {
                if (i < wordsInFilesVector.size()) {
                    std::string temps( (std::istreambuf_iterator<char>(inputFile)),
                                       (std::istreambuf_iterator<char>()));

                    wordsInFilesVector[i] = temps;

                }
                inputFile.close();
            } else {
                std::cout << "file couldn't open\n";
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
        for(int i = 0; i<requests.size(); ++i)
        {
            requests[i] = JSONservant["requests"][i];
        }

        return requests;
    }

    return std::vector<std::string>();
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
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
                JSONrank["docid:"] = a.first;
                JSONrank["rank:"] = a.second;
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
