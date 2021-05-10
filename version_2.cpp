#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "version_2.h" 

// https://stackoverflow.com/questions/21873048/getting-an-error-fopen-this-function-or-variable-may-be-unsafe-when-complin/21873153
#pragma warning(disable:4996);

static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
	return written;
}

// https://curl.se/libcurl/c/url2file.html
int extract_serverini_file()
{
    CURL* curl;
    FILE* fp;
    CURLcode res;
    const char* url = "http://osce14-p.activeupdate.trendmicro.com/activeupdate/server.ini";
    /* Warning, there is an issue with the line below that has wasted 3 hours of my day. Work out the issue and never repeat again.
    // char outfilename[FILENAME_MAX] = "C:\\Users\\Anthony\\source\\repos\\Smart_Scan_Pattern_Extractor - URL_Builder\\abc.txt";
    */
    char outfilename[FILENAME_MAX] = "I:\\123\\abc.txt";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename, "wb");
        // curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debug_callback);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
}

void testing()
{
	std::cout << "HELLO WORLD" << "\n\n";
}
