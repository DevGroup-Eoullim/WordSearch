#pragma once

#include <curl/curl.h>
#include "framework.h"
#include "dictionary.h"

class Searcher {
private:
	CURL* curl;
	//size_t HTTPCallback(size_t size, size_t nmemb, void* userdata, void* ptr);
	//size_t HTTPCallback(void* ptr, size_t size, size_t nmemb, void* userdata);
	struct curl_slist* headers = NULL;
	char resData[2048] = { 0 };
public:
	Searcher(); 
	~Searcher();
	DictionaryData* SearchWord(CString word);
};
struct memory {
	char response[CURL_MAX_WRITE_SIZE];
	size_t size;
};

size_t HTTPCallback(void* ptr,size_t size, size_t nmemb, void* userdata);