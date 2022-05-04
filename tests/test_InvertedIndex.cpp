#include "gtest/gtest.h"
#include "InvertedIndex.h"
#include <fstream>

TEST(InvertedIndex, update_freq_dict1){
    std::ofstream file("test.txt");
    std::string s = "one two three four five six seven";
    file << s;
    file.close();
    FreqDict freq_dict;
    std::stringstream ss;
    ss << s;
    while (!ss.eof()){
        std::string word;
        ss >> word;
        freq_dict[word] = {{0,1}};
    }

    InvertedIndex idx;
    idx.update_freq_dict({"test.txt"});
    std::remove("test.txt");
    EXPECT_EQ(idx.get_freq_dict(), freq_dict);
}

TEST(InvertedIndex, update_freq_dict2){
    std::vector<std::string> files = {
            "test1.txt",
            "test2.txt",
            "test3.txt",
            "test4.txt",
            "test5.txt"
    };
    for (auto& name : files){
        std::ofstream file(name);
        std::string s = "one two two three three three";
        file << s;
        file.close();
    }
    FreqDict freq_dict;
    for (size_t i = 0; i < 5; ++i) {
        freq_dict["one"].push_back({i, 1});
        freq_dict["two"].push_back({i, 2});
        freq_dict["three"].push_back({i, 3});
    }

    InvertedIndex idx;
    idx.update_freq_dict(files);
    for (const auto& name : files){
        std::remove(name.c_str());
    }
    EXPECT_EQ(idx.get_freq_dict(), freq_dict);
}