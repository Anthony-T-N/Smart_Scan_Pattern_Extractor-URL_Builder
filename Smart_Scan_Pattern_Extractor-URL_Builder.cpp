// Smart_Scan_Pattern_Extractor-URL_Builder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>

static std::string first_section = "http://osce14-p.activeupdate.trendmicro.com/activeupdate/";

void extract_serverini_file()
{
    // To be developed in version 2.
}
std::string sig_builder(std::string extracted_string)
{
    // Assumes extracted string has been processed by the url_builder(str) function.
    extracted_string.erase(extracted_string.find_last_of(".") + 1);
    return extracted_string + "sig";
}
std::string url_builder(std::string extracted_string)
{
    extracted_string.erase(extracted_string.find_first_of(","));
    extracted_string.erase(0, extracted_string.find_first_of("=") + 1);
    std::string final_string = first_section + extracted_string;
    return final_string;
}
std::string get_current_time()
{
    // Function uses: <chrono>
    // === Requires better understanding here === 
    // https://stackoverflow.com/questions/62226043/how-to-get-the-current-time-in-c-in-a-safe-way
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char tmBuff[30];
    ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
    return tmBuff;
}
void handle_text_file()
{
    // Function uses: <iostream>, <fstream>, <string>

    // https://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
    // ifstream vs ofstream
    // ifstream represents input file stream.
    std::ifstream URL_input_file;
    std::cout << "[!] Opening toread.txt for reading;" << "\n";
    if (std::filesystem::exists("toread.txt") == false)
    {
        std::cout << "[-] Unable to open toread.txt;" << "\n";
        return;
    }
    URL_input_file.open("toread.txt");
    std::cout << "[+] Opened toread.txt successfully;" << "\n\n";
    
    // ofstream represents output fle stream.
    std::cout << "[!] Creating output.txt;" << "\n";
    std::ofstream output_file;
    output_file.open("output.txt");
    std::cout << "[+] Created output.txt successfully;" << "\n\n";
    output_file << "Smart Scan Pattern(s) URLS Extracted on " << get_current_time() << "\n";
    std::string str;
    while (std::getline(URL_input_file, str))
    {
        //std::cout << str << "\n";
        if (str.find("MergeCountEx") != std::string::npos)
        {
            std::cout << "[!] MergeCountEx Found;" << "\n\n";
            continue;
        }
        std::string extracted_string = url_builder(str);
        std::cout << extracted_string << "\n";
        output_file << extracted_string << "\n";
        std::cout << sig_builder(extracted_string) << "\n\n";
        output_file << sig_builder(extracted_string) << "\n\n";
    }
    output_file.close();
    URL_input_file.close();
}
int main()
{
    std::cout << "=======================================" << "\n";
    std::cout << "- Welcome to the Smart_Scan_Pattern_Extractor-URL_Builder console application" << "\n";
    std::cout << "- Console Application Version: 1.0" << "\n";
    std::cout << "- Created By: Anthony N." << "\n";
    // https://en.cppreference.com/w/cpp/filesystem/current_path
    std::cout << "- Current location of executable: " << std::filesystem::current_path() << "\n";
    std::cout << "=======================================" << "\n\n";
    std::cout << "Prerequisites: 1) Smart Scan Patterns from Trend Micro has been copied to ""toread.txt"" Examples: Lines containing pattern/icrc/ioth_XXXXXXX" << "\n\n";
    if (std::filesystem::exists("output.txt") == true)
    {
        char recommence = '!';
        while (recommence != 'n' || recommence != 'y')
        {
            std::cout << "[=] output.txt already exist. Continue ? [Y/N]" << "\n";
            std::cin >> recommence;
            recommence = tolower(recommence);
            if (recommence == 'n')
            {
                return 0;
            }
            else if (recommence == 'y')
            {
                break;
            }
        }
    }
    handle_text_file();
    std::cout << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n\n";
}
