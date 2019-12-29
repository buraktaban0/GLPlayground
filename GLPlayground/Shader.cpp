#include "Shader.h"

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <stdexcept>

#include <vector>

#include <filesystem>
#include <iostream>

#include "io.h"

namespace fs = std::filesystem;

#define prefix "shaders\\"
#define vertexExt "_vertex.shader"
#define fragExt "_fragment.shader"


std::map<std::string, Shader> g_shaders;



void Shader::compileAll()
{

	std::vector<std::string> shaderNames;

	std::string path = "shaders";
	for (const auto& entry : fs::directory_iterator(path))
	{
		std::string path = entry.path().string();
		replace(path, vertexExt, "");
		replace(path, fragExt, "");
		replace(path, prefix, "");

		if (std::find(shaderNames.begin(), shaderNames.end(), path) == shaderNames.end())
		{
			shaderNames.push_back(path);
		}
	}

	for (const auto& name : shaderNames)
	{

		Shader shader = Shader(name);

		shader.compile();

		g_shaders[name] = shader;


	}

}



Shader* Shader::get(std::string name)
{

	if (g_shaders.count(name) < 1)
	{
		throw std::invalid_argument("No compiled program named " + name);
	}

	return &g_shaders[name];
}



Shader::Shader()
{
	this->c_programID = 0;
	this->c_name = "Undefined Shader";
}

Shader::Shader(std::string name)
{
	this->c_programID = 0;
	this->c_name = name;
}

unsigned int Shader::programID()
{
	return c_programID;
}


void Shader::compile()
{

	std::cout << "Compiling shader program '" << c_name << "'" << std::endl;

	auto vertexPath = prefix + c_name + vertexExt;
	auto fragPath = prefix + c_name + fragExt;

	std::string vertexSource = read_file(vertexPath);
	std::string fragSource = read_file(fragPath);
	const char* c_vert = vertexSource.c_str();
	const char* c_frag = fragSource.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &c_vert, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		throw std::invalid_argument("Vertex shader compilation failed");
	}

	glShaderSource(fragShader, 1, &c_frag, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		throw std::invalid_argument("Fragment shader compilation failed");
	}


	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		throw std::invalid_argument("Shader program link failed");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	c_programID = shaderProgram;


	c_modelLoc = glGetUniformLocation(c_programID, "model");

}

void Shader::setModelMat(glm::mat4 model)
{
	glUniformMatrix4fv(c_modelLoc, 1, GL_FALSE, &model[0][0]);
}


void Shader::use()
{
	//std::cout << "Shader: " << c_programID << std::endl;

	glUseProgram(c_programID);
}
