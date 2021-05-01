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

void handle_text_file()
{
    // Function uses: <iostream>, <fstream>, <string>, <chrono>

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
    // ofsteam represents output fle stream.
    std::cout << "[!] Creating output.txt;" << "\n";
    std::ofstream output_file;
    output_file.open("output.txt");
    std::cout << "[+] Created output.txt successfully;" << "\n\n";
    // TODO: Print time/date in first line of "output.txt" file here.
    // === Requires better understanding here === 
    // https://stackoverflow.com/questions/62226043/how-to-get-the-current-time-in-c-in-a-safe-way
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char tmBuff[30];
    ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
    std::cout << tmBuff << '\n';
    output_file << "URLS Extracted on " << tmBuff << "\n";
    // ========= 
    std::string str;
    while (std::getline(URL_input_file, str))
    {
        //std::cout << str << "\n";
        if (str.find("MergeCountEx") != std::string::npos)
        {
            std::cout << "[!] MergeCountEx Found;" << "\n";
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
    std::cout << "Welcome to the Smart_Scan_Pattern_Extractor-URL_Builder console application" << "\n";
    std::cout << "Created By: Anthony" << "\n";
    std::cout << "=======================================" << "\n\n";
    // https://en.cppreference.com/w/cpp/filesystem/current_path
    std::cout << "Current location of executable: " << std::filesystem::current_path() << "\n\n";
    std::cout << "Prerequisites: 1) Smart Scan Patterns from Trend Micro has been copied to ""toread.text"" Examples: Lines containing pattern/icrc/ioth_XXXXXXX" << "\n\n";
    handle_text_file();
    std::cout << "END OF PROGRAM" << "\n\n";
    std::cout << "[!] Exiting..." << "\n\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
