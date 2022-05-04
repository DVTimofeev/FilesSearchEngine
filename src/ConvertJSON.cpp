#include "ConvertJSON.h"

#include <typeinfo>
#include <fstream>



std::vector<std::string> ConvertJSON::get_file_paths(){
    return {_config["files"].begin(), _config["files"].end()};
}

std::vector<std::string> ConvertJSON::get_requests(){ 
    return {_requests["requests"].begin(), _requests["requests"].end()};
}

std::vector<std::string> ConvertJSON::get_document_text(int doc_number){
    std::vector<std::string> doc_text;
    if (doc_number < get_doc_count()){
        std::string line;
        std::ifstream input_file(_config["files"][doc_number].dump());
        while (std::getline(input_file, line)){
            doc_text.emplace_back(line);
        }
        input_file.close();
        return doc_text;
    }
    return doc_text;
}

std::unordered_set<std::string> ConvertJSON::get_document_text_wordset(int doc_number){
    if (doc_number < get_doc_count()){
        std::ifstream input_file(_config["files"][doc_number].dump());
        std::unordered_set<std::string> text_words = {std::istream_iterator<std::string>(input_file), std::istream_iterator<std::string>()};
        input_file.close();
        return text_words;
    }
    return std::unordered_set<std::string>();
}

std::unordered_set<std::string> ConvertJSON::get_request_wordset(int request_number){
    if (request_number < get_doc_count()){
        std::ifstream input_file(_requests["requests"][request_number].dump());
        std::unordered_set<std::string> text_words = {std::istream_iterator<std::string>(input_file), std::istream_iterator<std::string>()};
        input_file.close();
        return text_words;
    }
    return std::unordered_set<std::string>();
}

int ConvertJSON::get_response_limit(){
    int response_limit;
    try{
        response_limit = std::stoi(_config["config"]["max_responses"].dump());
    }
    catch(...){
        return 5; // if field is missing or has incorrect data, default parameter is returned
    }
    return response_limit;
}

//TODO the question is: What type of data funt recieves and how converts it in json to write a file
void ConvertJSON::save_answers(std::vector<std::vector<std::pair<int, double>>> answers_vec){
    json j;
    std::stringstream ss;
    size_t i = 0;
    for (const auto& results : answers_vec){
        i++;
        ss << "request" << std::setw(3) << std::setfill('0') << i;
        std::string request_id;
        ss >> request_id;
        ss.clear();
        if (results.empty()){
            j["answers"][request_id]["result"] = "false";
        }else{
            j["answers"][request_id]["result"] = "true";
            for(const auto& relevance : results){
                j["answers"][request_id]["relevance"] += {{"doc_id", relevance.first}, {"rank", relevance.second}};
            }
        }
    }
    
    std::ofstream output("answers.json");
    output << j.dump(4);

    output.close();
}

void ConvertJSON::open_config (std::string config_path){
    try {
        if (config_path.empty()) config_path = "config.json";
        std::ifstream file(config_path);
        if (!file.is_open()) {
            file.close();
            throw std::runtime_error("\"config.json\" is missing");
        }
        file >> _config;
        file.close();
    }catch(std::exception& re){
        _error_msg = re.what();
    }
}
void ConvertJSON::open_requests (std::string requests_path){
    try {
        if (requests_path.empty()) requests_path = "requests.json";
        std::ifstream file(requests_path);
        if (!file.is_open()) {
            file.close();
            throw std::runtime_error("\"requests.json\" is missing");
        }
        file >> _requests;
        file.close();
    }catch(std::exception& re){
        _error_msg = re.what();
    }
}

bool ConvertJSON::is_config_open(){
    return !(_config.empty());
}

bool ConvertJSON::is_requests_open(){
    return !(_requests.empty());

}

std::string ConvertJSON::get_error_msg(){
    return _error_msg;
}

int ConvertJSON::get_doc_count(){
    return _config["files"].size();
}

int ConvertJSON::get_request_count(){
    return _requests["requests"].size();
}

