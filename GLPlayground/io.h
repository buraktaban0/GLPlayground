#pragma once

#include <string>

bool replace(std::string& str, const std::string& from, const std::string& to);

std::string read_file(std::string);

void for_all_files(std::string path, void (*fptr)(std::string));