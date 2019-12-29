#include <fstream>
#include <string>


std::string read_all_file(std::string path)
{

	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;

}