#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "version_2.h" 

#pragma warning(disable:4996);

static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
	return written;
}

int magic()
{
    CURL* curl;
    FILE* fp;
    CURLcode res;
    int debug_callback(CURL * handle, curl_infotype type, char* data, size_t size, void* userptr);
    const char* url = "https://osce14-p.activeupdate.trendmicro.com/activeupdate/server.ini";
    char outfilename[FILENAME_MAX] = "C:\\Users\\Anthony\\source\\repos\\Smart_Scan_Pattern_Extractor - URL_Builder\\abc.txt";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debug_callback);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
}

void testing()
{
	std::cout << "HELLO WORLD" << "\n\n";
}

void extract_serverini_file()
{
	// To be developed in version 2.
}
