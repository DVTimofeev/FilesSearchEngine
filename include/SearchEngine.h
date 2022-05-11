#pragma once
#include "ISearchEngine.h"

#include <iostream>
#include <unordered_set>

using FreqDict = std::unordered_map<std::string, std::vector<Entry>>;

class SearchEngine : public ISearchEngine
{
private:
    std::vector<std::unordered_set<std::string>> _query_set;
    FreqDict _freq_dict;
    int _response_limit = 5;

public:
    SearchEngine(IInvertedIndex& idx);
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input) override;
    std::vector<RelativeIndex> search(std::string query) override;
    void set_response_limit(int limit) override;
};
