#pragma once
#include "IConvertJSON.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class ConvertJSON : public IConvertJSON{
public:
    ConvertJSON() = default;
    std::vector<std::string> get_file_paths() override;
    std::vector<std::string> get_requests() override;
    void save_answers(std::vector<std::vector<std::pair<int, double>>> answers) override;
    int get_response_limit() override;
    void open_config (std::string config_path) override;
    void open_requests (std::string requests_path) override;
    bool is_config_open() override;
    bool is_requests_open() override;
    std::string get_error_msg() override;
    int get_doc_count() override;
    int get_request_count() override;

    std::vector<std::string> get_document_text(int doc_number);
    std::unordered_set<std::string> get_document_text_wordset(int doc_number);
    std::unordered_set<std::string> get_request_wordset(int request_number);

private:
    json _config;
    json _requests;
    json _answers;
    
    std::string _error_msg = "";
};