#pragma once
#include <vector>
#include <unordered_set>

class IConvertJSON{
protected:
    virtual ~IConvertJSON() = default;
    
public:
    virtual std::vector<std::string> get_file_paths() = 0;
    virtual std::vector<std::string> get_requests() = 0;
    virtual int get_request_count() = 0;

    virtual void save_answers(std::vector<std::vector<std::pair<int, double>>> answers) = 0;

    virtual std::string get_error_msg() = 0;

    virtual void open_config (std::string config_pash) = 0;
    virtual void open_requests (std::string requests_pash) = 0;

    virtual bool is_config_open() = 0;
    virtual bool is_requests_open() = 0;

    virtual int get_response_limit() = 0;
    virtual int get_doc_count() = 0;

};