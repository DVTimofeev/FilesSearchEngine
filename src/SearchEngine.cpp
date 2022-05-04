#include "SearchEngine.h"

#include <sstream>
#include <iterator>
#include <algorithm>
#include <iomanip>


SearchEngine::SearchEngine(IInvertedIndex& idx){
    _freq_dict = idx.get_freq_dict();
}

std::vector<std::vector<RelativeIndex>> SearchEngine::search(const std::vector<std::string>& queries_input){
    std::vector<std::vector<RelativeIndex>> result;
    for (auto &&query : queries_input)
    {
        result.emplace_back(this->search(query));
    }
    return result;
}

std::vector<RelativeIndex> SearchEngine::search(std::string query){
    std::vector<RelativeIndex> result(_response_limit);
    std::stringstream ss;
    std::transform(query.begin(), query.end(), query.begin(), tolower);
    ss << query;
    std::unordered_set<std::string> query_set = {std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>()};
    float min_rank = 0;
    std::unordered_map<size_t, float> relative_map;
    for (auto &word : query_set)
    {
        for (auto &entry : _freq_dict[word])
        {
            relative_map[entry.doc_id] += entry.count;               
        }
    }

    if (relative_map.empty()){
        return {}; //return empty vector
    }

    for (auto &&r_map : relative_map)
    {
        if (r_map.second > min_rank){
                RelativeIndex r_idx = {r_map.first, r_map.second};

                for (size_t i = 0; i < result.size(); i++)
                {
                    if (r_map.second > result[i].rank){
                        result.insert(result.begin() + i, r_idx);
                        break;
                    }
                }
                result.pop_back();
                min_rank = result.back().rank;
                
            }
    }
    
    
    int max = result[0].rank;
    for (auto &&i : result)
    {
        i.rank /= max;
        std::stringstream ss;
        ss << std::setprecision(3) << i.rank;
        ss >> i.rank;
        ss.clear();
    }
    
    return result;
}


void SearchEngine::set_response_limit(size_t limit){
    if (limit > 0) {
        _response_limit = limit;
    }
}


