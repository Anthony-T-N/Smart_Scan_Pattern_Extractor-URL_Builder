#define CURL_STATICLIB
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "version_2.h" 
#include <filesystem>

void comment_server_section();

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
    // Warning, there is an issue with the line below that has wasted 3 hours of my day. Work out the issue and never repeat again.
    // char outfilename[FILENAME_MAX] = "C:\\Users\\Anthony\\source\\repos\\Smart_Scan_Pattern_Extractor - URL_Builder\\abc.txt";
    
    std::string inifile = std::filesystem::current_path().string() + "\\server.ini";
    char outfilename[FILENAME_MAX];
    // https://stackoverflow.com/questions/41915130/initializing-an-array-of-characters-with-a-string-variable
    strcpy(outfilename, inifile.c_str());
    std::cout << outfilename << "\n";
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
    comment_server_section();
    return 0;
}

void comment_server_section()
{
    // TODO:
    // - Open server.ini file and prepare for reading.
    // - Comment out [Server] section of file and stop at next empty line.
    // - Save file once commenting is completed

    std::ifstream input_file;
    std::cout << "[!] Opening server.ini for reading;" << "\n";
    if (std::filesystem::exists("server.ini") == false)
    {
        std::cout << "[-] Unable to open server.ini;" << "\n";
        return;
    }
    input_file.open("server.ini");
    std::cout << "[+] Opened server.ini successfully;" << "\n\n";

    std::ofstream output_file;
    output_file.open("temp.txt");
    std::cout << "[+] Created temp.txt successfully;" << "\n\n";

    // Cannot edit individual lines of an existing text file. Edited copy will need to be made.
    std::string input_file_line;
    bool commenting_enabled = false;
    while (std::getline(input_file, input_file_line))
    {
        if (input_file_line.find("[Server]") != std::string::npos)
        {
            std::cout << "[+] [Server] Section Found;" << "\n";
            std::cout << input_file_line << "\n\n";
            commenting_enabled = true;
        }
        // Section here to end commenting.
        if (commenting_enabled == true)
        {
            input_file_line = ";" + input_file_line;
        }
        std::cout << input_file_line << "\n";
        output_file << input_file_line << "\n";
    }
    input_file.close();
    output_file.close();

}
