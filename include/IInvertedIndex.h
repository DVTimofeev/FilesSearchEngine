#pragma once
#include <unordered_map>
#include <vector>

struct Entry
{
    size_t doc_id, count;
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class IInvertedIndex{
protected:
    virtual ~IInvertedIndex() = default;
public:
    virtual std::unordered_map<std::string, std::vector<Entry>> get_freq_dict() = 0;
    virtual void update_freq_dict(const std::vector<std::string> &filepaths) = 0;

private:

};