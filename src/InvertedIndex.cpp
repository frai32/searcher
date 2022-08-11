#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {

    docs = input_docs;

    for(auto& doc : docs)
    {
        std::istringstream fileString(doc);
        while (!fileString.eof())
        {
            std::string singlString;
            fileString>>singlString;
            freq_dictionary.insert(std::pair<std::string , std::vector<Entry>>(singlString, GetWordCount(singlString)));
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {

    std::vector<Entry> dictionary;
    for(size_t i =0; i<docs.size(); ++i) {
        size_t _count = 0;
        std::istringstream fileString(docs[i]);
        while (!fileString.eof()) {
            std::string singlString;
            fileString >> singlString;
            if (singlString == word)
                _count++;
        }
        if (_count > 0) {
            Entry much = {.doc_id = i, .count = _count};
            dictionary.emplace_back(much);
        }
    }
    return dictionary;
}

std::map<std::string, std::vector<Entry>> InvertedIndex::GetFreq_Dictionary() {
    return freq_dictionary;
}


