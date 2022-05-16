# Simple Search Engine   
Application for searching requests in text files.  

## Content:
* [Description](#Description)
* [Dependencies](#Dependencies)
* [Build](#Build)
* [Methods Description](#Methods_Description)
* [App Starting](#App_Starting)

### <a name="Description">Description</a>
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

### <a name="Dependencies">Dependencies</a>


#### [nlohmann/json](https://github.com/nlohmann/json)

- **Intuitive syntax**.  
Simple Serialization / Deserialization.
You can also use streams to serialize and deserialize:

- **STL-like access**.  
Supports methods: "push_back(), size(), empty(), type(), clear()" and many more.

- **Easy integration**.  
You need to add a single json.hpp to use it.
  

#### [bshoshany/thread-pool](https://github.com/nlohmann/json)

a

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

aa

a
## Build
