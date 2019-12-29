#pragma once

#include <string>
#include <map>


class Texture
{
	static std::map<std::string, Texture*> s_loadedTextures;


	std::string c_path;

	unsigned char* c_data;

	int c_width, c_height, c_channelCount;

	unsigned int c_id;

	Texture();

	void uploadToGPU();

public:

	static Texture* get(std::string);

	static void load(std::string path);

	static void loadAll();


	std::string path();

	int width();
	int height();
	int channelCount();

	void use();

};

