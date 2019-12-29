#pragma once

#include <map>
#include <string>

class Shader
{


	std::string c_name;

	unsigned int c_programID;

	std::map<std::string, unsigned int> c_uniformLocations;



public:


	static void compileAll();

	static Shader get(std::string);




	Shader();
	Shader(std::string name);

	unsigned int programID();

	void compile();

	void use();

};

