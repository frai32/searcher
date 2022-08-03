#pragma once
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "InvertedIndex.h"
#include "ConverterJSON.h"



struct RelativeIndex
{
    size_t doc_id{0};
    float rank{0};

    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};


class SearchServer {

public:
    /**
    * @param idx в конструктор класса передаётся ссылка на класс
    InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов встречаемых в
    запросе
    */
    SearchServer(InvertedIndex& idx);

    /**
    * Метод обработки поисковых запросов
    * @param queries_input поисковые запросы взятые из файла
    requests.json
    * @return возвращает отсортированный список релевантных ответов для
    заданных запросов
    */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);


private:

    std::vector<std::string> parse_request_into_vector(const std::string& str);

    std::map<std::string, float> get_indexes_for_request_words(std::vector<std::string>& vec);

    void ThreadSearch(const std::string &query, std::vector<RelativeIndex>& ref);

    InvertedIndex _index;

    std::mutex indexMutex;

};

