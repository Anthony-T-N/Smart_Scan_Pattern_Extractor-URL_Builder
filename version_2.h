#ifndef VERSION_2_H
#define VERSION_2_H

int extract_serverini_file();
void comment_server_section();
void directories_structure();
void icrc_pattern_identification();

std::string url_builder(std::string extracted_string);
std::string sig_builder(std::string extracted_string);

#endif
