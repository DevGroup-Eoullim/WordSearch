#include "searcher.h"
#include <cjson/cJSON.h>




Searcher::Searcher() {
	curl_global_init(CURL_GLOBAL_ALL);

	CURLcode result;

	curl = curl_easy_init();
	result=curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	if (result!=CURLE_OK) {
		fprintf(stderr, "CURLOPT_SSL_VERIFYPEER error: %s\n", curl_easy_strerror(result));
	}

	result=curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPCallback);
	if (result != CURLE_OK) {
		fprintf(stderr, "CURLOPT_WRITEFUNCTION error: %s\n", curl_easy_strerror(result));
	}

	headers = curl_slist_append(headers, "Content-Type: application/json; charset=utf-8");
	result=curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	if (result != CURLE_OK) {
		fprintf(stderr, "CURLOPT_HTTPHEADER error: %s\n", curl_easy_strerror(result));
	}

	result = curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
	if (result != CURLE_OK) {
		fprintf(stderr, "CURLOPT_FAILONERROR error: %s\n", curl_easy_strerror(result));
	}

	
}
Searcher::~Searcher() {
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}
DictionaryData* Searcher::SearchWord(CString word) {
	CString tUrl;

	CStringA str;
	CString res;

	DictionaryData* dictData = NULL;


	tUrl.Format(_T("https://api.dictionaryapi.dev/api/v2/entries/en/%s"), word);
	CStringA url = CStringA(tUrl);
	printf("%s\n", url);
	memory buf = { 0 };

	if (curl) {
		CURLcode result;

		result = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&buf);
		if (result != CURLE_OK) {
			fprintf(stderr, "CURLOPT_WRITEDATA error: %s\n", curl_easy_strerror(result));
			return NULL;
		}

		result = curl_easy_setopt(curl, CURLOPT_URL, url);
		if (result != CURLE_OK) {
			fprintf(stderr, "CURLOPT_URL failed: %s\n", curl_easy_strerror(result));
			return NULL;
		}

		result = curl_easy_perform(curl);
		if (result != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			return NULL;
		}

		//printf("%s\n", buf.response);
		cJSON* json = cJSON_Parse(buf.response);
		str = cJSON_Print(json);
		res = ConvertUTF8ToCStringW(str);

		dictData =new DictionaryData(json);

		cJSON_Delete(json);
	}

	return dictData;
}



size_t HTTPCallback(void* ptr,size_t size, size_t nmemb, void* userdata) {
	size_t realSize = size * nmemb;
	memory* mem = (memory*)userdata;

	memcpy(&(mem->response[mem->size]), ptr, realSize);
	mem->size += realSize;
	mem->response[mem->size] = 0;

	return realSize;
}