#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "SearchServer.h"
#include "CONFIGMissingExeption.h"
#include "REQUESTSMissingExeption.h"

struct RelativeIndex;

class ConverterJSON {
public:

    ConverterJSON() = default;

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    std::vector<std::string> GetTextDocument();

    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */
    int GetResponsesLimit();

    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string> GetRequests();

    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    void putAnswers(std::vector<std::vector<RelativeIndex>>);

    /**
     * Проверка на корекктность файла config.json
     */
     void checkConfigs();
     void checkRequests();
     bool getIsEmpty();

private:
    std::ofstream outputFile;
    std::ifstream inputFile;
    bool isEmpty; //если в файле requests.json есть запросы, или файла нет то значение будет true

};



