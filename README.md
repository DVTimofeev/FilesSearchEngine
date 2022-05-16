# Simple Search Engine   
Application for searching requests in text files.  

## Content
* [Description](#description)
* [Dependencies](#dependencies)
* [Build](#build)
* [Methods Description](#methods-description)
* [App Starting](#app-starting)

### Description
It is necessary to develop a search engine that can be used to search query in set of documents.
The search engine should represent the console application,search and capable of setting through files
format [JSON](https://www.json.org/json-ru.html).

How a search engine works:
1. In the configuration file (config.json), before starting the application, the names of the files that the engine will search for are specified.
2. The search engine independently bypasses all files and indexes them so that it can then find the most relevant documents for any search query.
3. The user sets the request via the requests.json JSON file. A query is a set of words to search for documents.
4. The query is transformed into a list of unique words.
5. The index looks for those documents that contain all these words.
6. Search results are ranked, sorted and returned to the user, the maximum number of possible documents in the response is set in the configuration file (config).
7. At the end, the program generates the answers.json file, into which it writes the search results.

### Dependencies


#### [nlohmann/json](https://github.com/nlohmann/json)

- **Intuitive syntax**.  
Simple Serialization / Deserialization.
You can also use streams to serialize and deserialize:

- **STL-like access**.  
Supports methods: "push_back(), size(), empty(), type(), clear()" and many more.

- **Easy integration**.  
You need to add a single json.hpp to use it.
  

#### [bshoshany/thread-pool](https://github.com/bshoshany/thread-pool)

- **Fast**:  
    - Built from scratch with maximum performance in mind.
    - Suitable for use in high-performance computing nodes with a very large number of CPU cores.
    - Compact code, to reduce both compilation time and binary size.
    - Reusing threads avoids the overhead of creating and destroying them for individual tasks.
    - A task queue ensures that there are never more threads running in parallel than allowed by the hardware.

- **Lightweight**:  
    - Only ~180 lines of code, excluding comments, blank lines, and the two optional helper classes.
    - Single header file: simply #include "thread_pool.hpp".
    - Header-only: no need to install or build the library.
    - Self-contained: no external requirements or dependencies. Does not require OpenMP or any other multithreading APIs. Only uses the C++ standard library, and works with any C++17-compliant compiler.

- **Easy to use**:  
    - Very simple operation, using a handful of member functions.
    - Every task submitted to the queue automatically generates an std::future, which can be used to wait for the task to finish executing and/or obtain its eventual return value.
    - Optionally, tasks may also be submitted without generating a future, sacrificing convenience for greater performance.
    - The code is thoroughly documented using Doxygen comments - not only the interface, but also the implementation, in case the user would like to make modifications.
    - The included test program thread_pool_test.cpp can be used to perform comprehensive automated tests and benchmarks, and also serves as an extensive example of how to properly use the package.


### Build

Create folder for build files and step into it

    mkdir build
    cd build

Run CMake to generate a buildsystem and then build target "SearchEngine" with "Release" config.

    cmake ..
    cmake --build . --config Release --target SearchEngine

The result file should be in Release folder in parent directory of the project.

### Methods Description

#### ConvertJSON
- void open_config (std::string config_path)  
opens a "config.json" file at the specified path, if there is no file or file could not be opened error msg is recorded. If an empty string is passed there will be attempt to open "config.json" in execution directory.

- void open_requests (std::string requests_path)  
opens a "requests.json" file at the specified path, if there is no file or file could not be opened error msg is recorded. If an empty string is passed there will be attempt to open "requests.json" in execution directory.

- std::string get_error_msg()  
get recorded message, if there is none return an empty string.

- bool is_config_open()  
return true if file is open and not empty;

- bool is_requests_open()  
return true if file is open and not empty;

- std::vector< std::string > get_file_paths()  
return vector of file paths specified in config.json

- int get_response_limit()  
return maximum number results for each query. The limit specified in config.json.

- int get_doc_count()  
return number of documents specified in config.json.

- std::vector< std::string > get_requests()
return vector of requests (querys) specified in requests.json

- int get_request_count()  
return number of requests specified in requests.json.

- void save_answers(std::vector<std::vector<std::pair<int, double>>> answers)  
create file answer.json and saveы the results of the search.

#### InvertedIndex

- void update_freq_dict(const std::vector< std::string> &filepaths)  
Еakes a vector of file paths as input, uses a thread pool to process each file and forms a dictionary of words and the corresponding frequency index, using which the most relevant result is determind.

- std::unordered_map< std::string, std::vector< Entry>> get_freq_dict()  
return dictionary of words and the corresponding frequency index.

#### SearchEngine

- void set_response_limit(int limit)  
set size limit of returned vector of the results

- std::vector< RelativeIndex> search(std::string query)  
return vector of results of processing a single query.

- std::vector< std::vector< RelativeIndex>> search(const std::vector< std::string>& queries_input)  
return vector of vectors of results of processing an array of queries.

### App Starting

For correct work of an app first step would be to construct ConvertJSON object and open config.json and requests.json

    ConvertJSON convertJSON;
    convertJSON.open_config("");
    convertJSON.open_requests("");

If there is an error, its better terminate the program and print error msg.

Otherwise we may proceed with reading file paths from "config.json"

    auto file_paths = convertJSON.get_file_paths();
    auto requests = convertJSON.get_requests();

Next step is to update frequency dictionary of invertedIndex

    InvertedIndex invertedIndex;
    invertedIndex.update_freq_dict(file_paths);

Step 3 is to initiate search and geting results

    SearchEngine searchEngine(invertedIndex);
    searchEngine.set_response_limit(convertJSON.get_response_limit());
    auto answers = searchEngine.search(requests);

With last step the results is needet to be converted in correct format to save them in the file

    std::vector<std::vector<std::pair<int, double>>> result;

    for (size_t i = 0; i < answers.size(); i++)
    {
        result.emplace_back();
        for (size_t j = 0; j < answers[i].size(); j++)
        {
            result[i].push_back({answers[i][j].doc_id, answers[i][j].rank});
        }
        
    }
    
    convertJSON.save_answers(result);

After saving the results operation of the program ending.