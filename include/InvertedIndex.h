#pragma once
#include "IInvertedIndex.h"
#include "thread-pool-2.0.0/thread_pool.hpp"


using FreqDict = std::unordered_map<std::string, std::vector<Entry>>;

class InvertedIndex : public IInvertedIndex{
public:
    InvertedIndex() = default;
    FreqDict get_freq_dict() override;
    void update_freq_dict(const std::vector<std::string> &filepaths) override;

private:
    FreqDict get_file_wordmap(const std::string &filepath, int doc_id);

    FreqDict _freq_dict;

};