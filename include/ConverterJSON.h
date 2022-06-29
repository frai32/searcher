#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "SearchServer.h"

struct RelativeIndex;

class ConverterJSON {
public:

    ConverterJSON() = default;

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    std::vector<std::string> getTextDocument();

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



private:
    std::ofstream outputFile;
    std::ifstream inputFile;

};



