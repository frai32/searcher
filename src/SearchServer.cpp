#include "SearchServer.h"
#include <algorithm>
#include <functional>
#include <chrono>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {

    std::vector<std::vector<RelativeIndex>> allIndexes;
    std::vector<std::thread> requestsTreads;
    for(size_t i = 0; i<queries_input.size(); ++i)
    {
       requestsTreads.emplace_back(&SearchServer::ThreadSearch, this,  queries_input[i], std::ref(allIndexes)).join();
    }

    return allIndexes;
}

SearchServer::SearchServer(InvertedIndex &idx) : _index(idx){
    //ConverterJSON json;
    //_index.UpdateDocumentBase(json.getTextDocument());
}

std::vector<std::string> SearchServer::parse_request_into_vector(const std::string &str) {
    std::stringstream  ss(str);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    return {begin, end};
}

std::map<std::string, float> SearchServer::get_indexes_for_request_words(std::vector<std::string> &vec) {

    auto dict = _index.GetFreq_Dictionary();
    std::map<std::string, float> m;
    for(auto& v:vec)
    {
        if(dict.count(v))
        {
            size_t sum = 0;
            std::for_each(dict[v].begin(),dict[v].end(), [&sum](auto& el)
            {
                sum += el.count;
            });
            m[v] = sum;
        }
    }

    return m;
}

void SearchServer::ThreadSearch(const std::string &query, std::vector<std::vector<RelativeIndex>>& ref) {

    std::unique_lock<std::mutex> uniqueMutex (indexMutex, std::defer_lock);

    uniqueMutex.lock();
        auto dict = _index.GetFreq_Dictionary();
   uniqueMutex.unlock();

    std::vector<std::string> vec{parse_request_into_vector(query)};
    std::map<std::string, float> request_absolute_index{get_indexes_for_request_words(vec)};

    std::multimap<float, std::string> absolute_index_request;
    for(auto& e : request_absolute_index) {
        absolute_index_request.insert(std::pair(e.second, e.first));
    }

    if(!absolute_index_request.empty()) {
        std::map<size_t, float> doc_id_absolute_index;
        for (auto it = dict[absolute_index_request.begin()->second].begin();
             it != dict[absolute_index_request.begin()->second].end();
             ++it
                ) {
            doc_id_absolute_index[it->doc_id] = 0; /* пока просто заполняем ключи в map */
        }

        for (auto &doc_id_frequency: dict) {
            /* частоту в map добавляем только если слово есть в запросе */
            if (query.find(doc_id_frequency.first) != std::string::npos) {
                for_each(doc_id_frequency.second.begin(), doc_id_frequency.second.end(),
                         [&doc_id_absolute_index](auto &item) {
                             /* Если слово есть в запросе и документ есть в map по самому редкому слову */
                             if (doc_id_absolute_index.count(item.doc_id))
                                 doc_id_absolute_index[item.doc_id] += item.count;
                         });
            }
        }

        std::multimap<size_t, float, std::greater<>> sorted_absolute_index;
        for (auto &e : doc_id_absolute_index) {
            sorted_absolute_index.insert(std::pair(e.second, e.first));
        }

        std::vector<RelativeIndex> vector_relative_index;
        for (auto &item: sorted_absolute_index) {
            RelativeIndex r{.doc_id = (size_t) item.second, .rank = (float) item.first /
                                                                    sorted_absolute_index.begin()->first};
            vector_relative_index.emplace_back(r);
        }

        uniqueMutex.lock();
        ref.emplace_back(vector_relative_index);
        uniqueMutex.unlock();
    }
    else
    {
        std::vector<RelativeIndex> vector_relative_index;
        uniqueMutex.lock();
        ref.emplace_back(vector_relative_index);
        uniqueMutex.unlock();

    }

}


