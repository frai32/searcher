# Searcher

## Discription

Application for searching information in local files

## description of the stack of technologies used

Aplication writing on C++ 20
Library for working with JSON: https://github.com/nlohmann/json#conversion-from-stl-containers
For using JSON library in project added json.hpp file.
Library for working with autotesting: https://github.com/google/googletest

## Launch parameters

For correct operation in the file config.JSON, it is necessary to indicate in square brackets against the "file" parameter a list of paths to the files in which you want to search. Olso you must create answers.json and requests.json.
In requests.json you must include requsts for search.

## Supported Platform

Windows 10 (64) or later

## Compiling

Prerequisites:

* On Windows:
	* MinGW with GCC or CLion


You can download CLion from [https://www.jetbrains.com/clion/] (official site). Then you need install MinGW. You can download it from [https://www.mingw-w64.org/downloads/] (official site). Choose MingW-W64-builds. 
Open project in CLion and check project settings. In Build, Exeption, Deployment tab, open Toolchain and check have the MinGW in list. If not click to the plus button and choose MinGW then add path to MinGW compiler to Enviroment line.
If you have Visual Studio, you can you VS compiler. 

## project structure

Project contain the following classes:

* ConverterJSON for working with JSON files. It have following methods:
	* std::vector<std::string> getTextDocument() File content retrieval method. Returns a list with the contents of the files listed.
	* int GetResponsesLimit() The method reads the max_responses field to determine the limit number of responses per request
	* std::vector<std::string> GetRequests() Method for receiving requests from the requests.json file. Returns a list of requests from the requests.json file.
	* void putAnswers(std::vector<std::vector<RelativeIndex>>) putting in to ansewer.json file result of search requests
	* Methods for checking config.json file
		* void checkConfigs() checking if config.json is exist
		* void checkRequests() checking if requests.json is exist
		* bool getIsEmpty() returns isEmpty fild
	* ConverterJSON contain fallowing filds:
		* std::ofstream outputFile for reading data from JSON files
		* std::ifstream inputFile for writing data into JSON files
* InvertedIndex for calculating inverted index of search request results. It have auxiliary structure Entry and following methods:
	*  void UpdateDocumentBase(std::vector<std::string> input_docs) Updating or filling base of documents to be searched
	*  std::vector<Entry> GetWordCount(const std::string& word) The method determines the number of occurrences of the "word" word in the loaded database documents. returns a prepared list with word frequency
	*  std::map<std::string, std::vector<Entry>> GetFreq_Dictionary() returns dictionary with words from all documents and their frequency index
	*InvertedIndex have following filds:
		* std::vector<std::string> docs list of document content
		* std::map<std::string, std::vector<Entry>> freq_dictionary in this fild writting words and thoes frequency index
* SearchServer have auxiliary structure RelativeIndex and fallowing methods:
	* std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input) method starts a thread for each request
	* std::vector<std::string> parse_request_into_vector(const std::string& str) breaks queries into separate words
	* std::map<std::string, float> get_indexes_for_request_words(std::vector<std::string>& vec) calculates index for each word
	* void ThreadSearch(const std::string &query, std::vector<RelativeIndex>& ref) make search for each request
	* SearchServer have following filds:
		* InvertedIndex _index this fild get indexes from documents
		* std::mutex indexMutex to control access to shared data
* REQUESTSMissingExeption class for requests.json file related errors, this class successor of exeption class and have ovveride what() method
* CONFIGMissingExeption class for config.json file related errors, this class successor of exeption class and have ovveride what() method	
		
		
## Example

The following example will show the basic operation of the application.

	while(isWork) 
    {
        std::cout<<"input command: ";
        std::cin>>comand;
		
        if(comand == "?")
        {
            showComands(); //Type '?' for showing comand list
        }
        else if(comand == "q") // finsh the program
        {
            std::cout<<"finish\n";
            isWork = false;
        }
        else if(comand == "s") //Make search
        {
            std::cout<<"start searching\n";
            ConverterJSON converter;
            InvertedIndex idx;
            idx.UpdateDocumentBase(converter.getTextDocument()); //Get information from *.txt files
            SearchServer srv(idx);
            converter.putAnswers(srv.search(converter.GetRequests()));// Put result to answer.json

            std::cout<<"Search completed. Check answers.json\n";
        }
        else
        {
            std::cout<<"Wrong command\n";
        }
    }	
