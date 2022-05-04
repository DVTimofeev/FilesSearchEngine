#include "gtest/gtest.h"
#include "InvertedIndex.h"
#include "SearchEngine.h"

#include <fstream>

TEST(SearchEngine, single_search){
    std::string s = "one two two three three three four four four four"
                    " five five five five five";
    std::stringstream ss;
    ss << s;
    std::vector<std::string> docs;
    s.clear();
    while (!ss.eof()){
        for (int i = 0; i < 3; ++i) {
            std::string temp;
            ss >> temp;
            s += temp + ' ';
        }
        docs.emplace_back(s);
    }
    std::vector<std::string> filepaths;
    for (size_t i = 0; i < docs.size(); ++i){
        filepaths.emplace_back("test" + std::to_string(i) + ".txt");
        std::ofstream file(filepaths.back());
        file << docs[i];
        file.close();
    }

    InvertedIndex idx;
    idx.update_freq_dict(filepaths);

    SearchEngine searchEngine(idx);

    std::vector<RelativeIndex> expected = {
        {4, 1},  
        {3, 0.667},
        {2, 0.444},
        {1, 0.444},
        {0, 0.111}
    };

    std::string query = "one three five";
    auto result = searchEngine.search(query);

    for (const auto& filename : filepaths){
        std::remove(filename.c_str());
    }
    
    EXPECT_EQ(result, expected);
}

TEST(SearchEngine, multi_search){
    std::string s = "one two two three three three four four four four"
                    " five five five five five";
    std::stringstream ss;
    ss << s;
    std::vector<std::string> docs;
    s.clear();
    while (!ss.eof()){
        for (int i = 0; i < 3; ++i) {
            std::string temp;
            ss >> temp;
            s += temp + ' ';
        }
        docs.emplace_back(s);
    }
    std::vector<std::string> filepaths;
    for (size_t i = 0; i < docs.size(); ++i){
        filepaths.emplace_back("test" + std::to_string(i) + ".txt");
        std::ofstream file(filepaths.back());
        file << docs[i];
        file.close();
    }

    InvertedIndex idx;
    idx.update_freq_dict(filepaths);

    SearchEngine searchEngine(idx);

    std::vector<std::vector<RelativeIndex>> expected = {
                    {
                        {4, 1},  
                        {3, 0.667},
                        {2, 0.444},
                        {1, 0.444},
                        {0, 0.111}
                    },
                    {   
                        {4, 1},  
                        {3, 0.571},
                        {2, 0.286},
                        {1, 0.286},
                        {0, 0.286}
                    },
                    {
                        {4, 1},  
                        {3, 1},
                        {2, 0.8},
                        {1, 0.2},
                        {0, 0.2}
                    },
                    {},
                    {
                        {4, 1},  
                        {3, 1},
                        {2, 1},
                        {1, 1},
                        {0, 1}
                    }

    };

    std::vector<std::string> query = {
        "one three five",
        "two five",
        "one four",
        "not a single word",
        "one"
    };
    auto results = searchEngine.search(query);

    for (const auto& filename : filepaths){
        std::remove(filename.c_str());
    }
   
    EXPECT_EQ(results, expected);
}
