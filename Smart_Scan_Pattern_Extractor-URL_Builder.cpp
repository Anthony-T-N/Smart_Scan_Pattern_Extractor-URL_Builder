// Smart_Scan_Pattern_Extractor-URL_Builder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

static std::string first_section = "http://osce14-p.activeupdate.trendmicro.com/activeupdate/";

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
    // https://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
    // ifstream vs ofstream
    std::ofstream out("output.txt");
    // TODO: Print time/date in first line of "output.txt" file here.
    std::ifstream myfile;
    myfile.open("toread.txt");
    std::string str;
    while (std::getline(myfile, str))
    {
        //std::cout << str << "\n";
        if (str.find("MergeCountEx") != std::string::npos)
        {
            std::cout << "[=] MergeCountEx Found" << "\n";
            continue;
        }
        std::string extracted_string = url_builder(str);
        std::cout << extracted_string << "\n";
        out << extracted_string << "\n";
        std::cout << sig_builder(extracted_string) << "\n\n";
        out << sig_builder(extracted_string) << "\n\n";
    }
    out.close();
    myfile.close();
}

int main()
{
    std::cout << "[=] << Begin >>" << "\n\n";
    handle_text_file();
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
