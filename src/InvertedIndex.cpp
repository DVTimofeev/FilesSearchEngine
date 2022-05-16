#include "InvertedIndex.h"

#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <iterator>
#include <algorithm>

FreqDict InvertedIndex::get_freq_dict(){
    return _freq_dict;
}


void InvertedIndex::update_freq_dict(const std::vector<std::string> &filepaths){
    std::vector<std::future<FreqDict>> ft_vec;
    thread_pool pool;
    
    for (int i = 0; i < filepaths.size(); i++){
        auto func = [this](const std::string& filepath, int doc_id){return get_file_wordmap(filepath, doc_id); };
        auto ft = pool.submit(func, filepaths[i], i);
        ft_vec.push_back(std::move(ft));
    }

    for (int i = 0; i < filepaths.size(); i++){
        auto ret = ft_vec[i].get();
        for (auto &&item : ret)
        {
            auto key = item.first;
            auto vec = item.second;
            _freq_dict[key].insert(_freq_dict[key].end(), vec.begin(), vec.end());
        }

    }
}

FreqDict InvertedIndex::get_file_wordmap(const std::string &filepath, int doc_id){
    std::unordered_map<std::string, std::vector<Entry>> result;
    std::ifstream input(filepath);
    std::istream_iterator<std::string> iit(input);
    while (iit != std::istream_iterator<std::string>())
    {
        std::string word = *iit;
        std::transform(word.begin(), word.end(), word.begin(), tolower);
        if (result.find(word) == result.end()){
            result[word].emplace_back();
            result[word][0].doc_id = doc_id;
        }
        result[word][0].count++;
        ++iit;
    }
    input.close();
    return result;
}
