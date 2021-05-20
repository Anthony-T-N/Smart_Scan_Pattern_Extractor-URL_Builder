#define CURL_STATICLIB
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "version_2.h" 
#include <filesystem>
#include <chrono>

// https://stackoverflow.com/questions/21873048/getting-an-error-fopen-this-function-or-variable-may-be-unsafe-when-complin/21873153
#pragma warning(disable:4996);

std::string current_root_folder = ""; 

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
    
    std::string inifile = std::filesystem::current_path().string() + "\\temp.ini";
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
    return 0;
}

void comment_server_section()
{
    // Function must occur after function directories_structure().
    std::ifstream input_file;
    std::cout << "[!] Opening temp.ini for reading;" << "\n";
    if (std::filesystem::exists("temp.ini") == false)
    {
        std::cout << "[-] Unable to open temp.ini;" << "\n";
        return;
    }
    input_file.open("temp.ini");
    std::cout << "[+] Opened temp.ini successfully;" << "\n\n";

    std::ofstream output_file;
    output_file.open(current_root_folder + "/server.ini");
    std::cout << "[+] Created server.ini successfully;" << "\n\n";

    // Cannot edit individual lines of an existing text file. Edited copy will need to be made.
    std::string input_file_line;
    bool commenting_enabled = false;
    bool server_section_found = false;
    while (std::getline(input_file, input_file_line))
    {
        if (input_file_line.find("[Server]") != std::string::npos)
        {
            std::cout << "[+] [Server] Section Found;" << "\n";
            std::cout << input_file_line << "\n\n";
            server_section_found = true;
            commenting_enabled = true;
            output_file << input_file_line << "\n";
            continue;
        }
        // Continue to comment [Server] section until empty space is located.
        if (commenting_enabled == true && input_file_line == "")
        {
            commenting_enabled = false;
        }
        if (commenting_enabled == true)
        {
            input_file_line = ";" + input_file_line;
        }
        output_file << input_file_line << "\n";
    }
    input_file.close();
    output_file.close();
    if (server_section_found == false)
    {
        std::cout << "[-] WARNING: [Server] Section Never Found;" << "\n";
        std::cout << "[-] Proceed with caution;" << "\n";
    }
    remove("temp.ini");
    std::cout << "[+] Deleted temp.ini successfully;" << "\n\n";
}

void directories_structure()
{
    // https://stackoverflow.com/questions/16357999/current-date-and-time-as-string/16358264
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    std::cout << buffer << "\n\n";

    std::string root_folder_name(buffer);
    std::filesystem::create_directories(root_folder_name + "/pattern/icrc");
    current_root_folder = root_folder_name;
}

// https://stackoverflow.com/questions/6951161/downloading-multiple-files-with-libcurl-in-c
void download_file(const char* url, const char* fname) 
{
    std::cout << "[!] Downloading: " << "\n";
    std::cout << url << "\n";
    std::cout << "To: " << "\n";
    std::cout << fname << "\n\n";

    CURL* curl;
    FILE* fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) 
    {
        fp = fopen(fname, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

std::string file_download_name(std::string url_name)
{
    url_name.erase(0, url_name.find_last_of("/") + 1);
    return url_name;
}

void icrc_pattern_identification()
{
    // Read server.ini file.
    std::ifstream input_file;
    std::cout << "[!] Opening server.ini for reading;" << "\n";
    if (std::filesystem::exists(current_root_folder + "/server.ini") == false)
    {
        std::cout << "[-] Unable to open server.ini;" << "\n";
        return;
    }
    input_file.open(current_root_folder + "/server.ini");
    std::string input_file_line;
    while (std::getline(input_file, input_file_line))
    {
        // Go through all lines in the "server.ini" file until line contains "icrc".
        if (input_file_line.find("icrc") != std::string::npos)
        {
            // Note: Function carried from main cpp file.
            std::string extracted_url = url_builder(input_file_line);
            std::string full_download_path = current_root_folder + "\\pattern\\icrc\\" + file_download_name(extracted_url);
            // https://stackoverflow.com/questions/9309961/how-to-convert-string-to-char-in-c
            /*
            * Question: Why can't these work ?
            * // https://stackoverflow.com/questions/9219712/c-array-expression-must-have-a-constant-value
            char* extracted_url_char = new char[extracted_url.length() + 1];
            char* full_download_path_char = new char[full_download_path.length() + 1];
            */

            /*
            std::string string_a = "abc";
            char* string_a_char[string_a.length() + 1];
            */
            
            char extracted_url_char[FILENAME_MAX];
            char full_download_path_char[FILENAME_MAX];

            strcpy(extracted_url_char, extracted_url.c_str());
            strcpy(full_download_path_char, full_download_path.c_str());
            download_file(extracted_url_char, full_download_path_char);
            
            // Note: Function carried from main cpp file.
            // Question: Reusing char arrays ?
            extracted_url = sig_builder(extracted_url);
            full_download_path = current_root_folder + "\\pattern\\icrc\\" + file_download_name(sig_builder(extracted_url));
            strcpy(extracted_url_char, extracted_url.c_str());
            strcpy(full_download_path_char, full_download_path.c_str());
            download_file(extracted_url_char, full_download_path_char);
        }
    }
    input_file.close();
}
