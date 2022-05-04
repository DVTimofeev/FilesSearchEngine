#include "gtest/gtest.h"
#include "ConvertJSON.h"
#include <fstream>

TEST(ConvertJSON, no_config_error_msg){
    ConvertJSON convertJson;
    convertJson.open_config("no_file.json");
    EXPECT_EQ(convertJson.get_error_msg(), "\"config.json\" is missing");
}

TEST(ConvertJSON, no_requests_error_msg){
    ConvertJSON convertJson;
    convertJson.open_requests("no_file.json");
    EXPECT_EQ(convertJson.get_error_msg(), "\"requests.json\" is missing");
}

TEST(ConvertJSON, open_config){
    ConvertJSON convertJson;
    std::ofstream file("test.json");
    json j;
    j["test"] = 5;
    file << j.dump(4);
    file.close();
    convertJson.open_config("test.json");
    std::remove("test.json");
    EXPECT_EQ(convertJson.is_config_open(), true);
}

TEST(ConvertJSON, open_requests){
    ConvertJSON convertJson;
    std::ofstream file("test_requests.json");
    json j;
    j["test_requests"] = "test_requests";
    file << j.dump(4);
    file.close();
    convertJson.open_requests("test_requests.json");
    std::remove("test_requests.json");
    EXPECT_EQ(convertJson.is_requests_open(), true);
}

TEST(ConvertJSON, get_file_paths){
    json j;
    std::vector<std::string> filepaths = {
            "/filepath/file1.txt",
            "/filepath/file2.txt",
            "/filepath/file3.txt",
            "/filepath/file4.txt",
            "/filepath/file5.txt"
    };
    std::ofstream file("test.json");
    j["files"] = filepaths;
    file << j.dump(4);
    file.close();

    ConvertJSON convertJson;
    convertJson.open_config("test.json");
    std::remove("test.json");

    EXPECT_EQ(convertJson.get_file_paths(), filepaths);
}

TEST(ConvertJSON, get_request) {
    json j;
    std::vector<std::string> requests = {
            "1 string of request",
            "2 string of request",
            "3 string of request",
            "4 string of request",
            "5 string of request"
    };
    std::ofstream file("test.json");
    j["requests"] = requests;
    file << j.dump(4);
    file.close();

    ConvertJSON convertJson;
    convertJson.open_requests("test.json");
    std::remove("test.json");

    EXPECT_EQ(convertJson.get_requests(), requests);
}

TEST(ConvertJSON, get_response_limit) {
    json j;
    std::ofstream file("test.json");
    j["config"]["max_responses"] = 11;
    file << j.dump(4);
    file.close();
    ConvertJSON convertJson;
    convertJson.open_config("test.json");
    EXPECT_EQ(convertJson.get_response_limit(), 11);
}

TEST(ConvertJSON, get_doc_count) {
    json j;
    std::vector<std::string> filepaths = {
            "/filepath/file1.txt",
            "/filepath/file2.txt",
            "/filepath/file3.txt",
            "/filepath/file4.txt",
            "/filepath/file5.txt"
    };
    std::ofstream file("test.json");
    j["files"] = filepaths;
    file << j.dump(4);
    file.close();

    ConvertJSON convertJson;
    convertJson.open_config("test.json");
    std::remove("test.json");
    EXPECT_EQ(convertJson.get_doc_count(), 5);
}

TEST(ConvertJSON, get_request_count) {
    json j;
    std::vector<std::string> requests = {
            "1 string of request",
            "2 string of request",
            "3 string of request",
            "4 string of request",
            "5 string of request"
    };
    std::ofstream file("test.json");
    j["requests"] = requests;
    file << j.dump(4);
    file.close();

    ConvertJSON convertJson;
    convertJson.open_requests("test.json");
    std::remove("test.json");
    EXPECT_EQ(convertJson.get_request_count(), 5);
}

TEST(ConvertJSON, save_answers) {
    ConvertJSON convertJson;
    std::vector<std::vector<std::pair<int, double>>> answers_vec;
    answers_vec = {
            {
                    {1, 1},
                    {0, 0.5},
                    {3, 0.3}
            },
            {},
            {
                    {0, 0.83},
                    {2, 0.7},
                    {5, 0.4}
            }

    };

    json reference = R"({
                    "answers": {
                        "request001": {
                            "relevance": [
                            {
                                "doc_id": 1,
                                        "rank": 1.0
                            },
                            {
                                "doc_id": 0,
                                        "rank": 0.5
                            },
                            {
                                "doc_id": 3,
                                        "rank": 0.3
                            }
                            ],
                            "result": "true"
                        },
                        "request002": {
                            "result": "false"
                        },
                        "request003": {
                            "relevance": [
                            {
                                "doc_id": 0,
                                        "rank": 0.83
                            },
                            {
                                "doc_id": 2,
                                        "rank": 0.7
                            },
                            {
                                "doc_id": 5,
                                        "rank": 0.4
                            }
                            ],
                            "result": "true"
                        }
                    }
                })"_json;

    convertJson.save_answers(answers_vec);
    std::ifstream file("answers.json");
    json saved;
    file >> saved;
    file.close();
    std::remove("answers.json");
    EXPECT_EQ(saved, reference);
}






