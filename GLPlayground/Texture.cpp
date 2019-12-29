#include "Texture.h"


#include <glad/glad.h>
#include <GLFW\glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

std::map<std::string, Texture*> Texture::s_loadedTextures;

Texture::Texture()
{
	this->c_width = 0;
	this->c_height = 0;
	this->c_channelCount = 0;
	this->c_id = 0;
	this->c_data = NULL;

}

std::string Texture::path() { return c_path; }
int Texture::width() { return c_width; }
int Texture::height() { return c_height; }
int Texture::channelCount() { return c_channelCount; }


void Texture::use()
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->c_id);

}


Texture* Texture::get(std::string path)
{

	if (Texture::s_loadedTextures.count(path) < 1)
	{
		throw std::invalid_argument("No loaded texture named: " + path);
	}

	return Texture::s_loadedTextures[path];
}


Texture* Texture::load(std::string path)
{

	int w, h, c;
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &c, 0);

	if (data)
	{

		Texture* tex = new Texture();
		tex->c_data = data;
		tex->c_width = w;
		tex->c_height = h;
		tex->c_channelCount = c;

		tex->uploadToGPU();

		Texture::s_loadedTextures[path] = tex;

		stbi_image_free(data);

		return tex;


	}

	std::cout << "DATA WAS NULL!" << std::endl;

	return NULL;

}


void Texture::uploadToGPU()
{
	unsigned int id;
	glGenTextures(1, &id);
	this->c_id = id;


	glBindTexture(GL_TEXTURE_2D, this->c_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (this->c_data)
	{

	}
	else
	{
		std::cout << "DATA WAS NULL 2 " << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->c_width, this->c_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->c_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);


}
