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
    std::vector<std::thread> th_vec;
    
    for (int i = 0; i < filepaths.size(); i++){
        auto func = [this](std::string filepath, int doc_id){return get_file_wordmap(filepath, doc_id); };
        std::packaged_task<FreqDict(std::string, int)> tsk(func);
        ft_vec.push_back(tsk.get_future());
        std::thread th(std::move(tsk), filepaths[i], i);
        th_vec.push_back(std::move(th));

    }
    for (int i = 0; i < filepaths.size(); i++){
        ft_vec[i].wait();    
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

    for (int i = 0; i < filepaths.size(); i++){
        th_vec[i].join();
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
