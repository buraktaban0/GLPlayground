#include <fstream>
#include <string>

#include <filesystem>

namespace fs = std::filesystem;


bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

std::string read_file(std::string path)
{

	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;

}


void for_all_files(std::string path, void (*fptr)(std::string))
{
	
	for (const auto& entry : fs::directory_iterator(path))
	{
		std::string file = entry.path().string();
		replace(file, "\\", "/");
		fptr(file);
	}

}