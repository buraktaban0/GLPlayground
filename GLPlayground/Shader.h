#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

class Shader
{


	std::string c_name;

	unsigned int c_programID;

	unsigned int c_modelLoc, c_viewLoc, c_projLoc;


	std::map<std::string, unsigned int> c_uniformLocations;


public:


	static void compileAll();

	static Shader* get(std::string);




	Shader();
	Shader(std::string name);

	unsigned int programID();

	void compile();

	void setModelMat(glm::mat4 model);

	void use();

};

