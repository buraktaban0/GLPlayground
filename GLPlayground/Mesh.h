#pragma once

#include "glmath.h"

#include "Texture.h"

struct VertexAttribute
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;

	VertexAttribute(glm::vec3 position, glm::vec3 color, glm::vec2 uv);

};

class Mesh
{

	unsigned int c_vao;

	unsigned int c_vertexCount = 3;


public:


	/**
	float vertices[12] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
	};
	*/

	glm::vec3 vertices[4] = {
		glm::vec3(0.5, 0.5, 0.0),
		glm::vec3(0.5, -0.5, 0.0),
		glm::vec3(-0.5, -0.5, 0.0),

	};

	VertexAttribute attributes[3] = {
		VertexAttribute(glm::vec3(0.5, -0.5, 0.0), glm::vec3(1.0, 0.0, 0), vec2right),
		VertexAttribute(glm::vec3(-0.5, -0.5, 0.0), glm::vec3(0, 1, 0), vec2zero),
		VertexAttribute(glm::vec3(0.0, 0.5, 0.0), glm::vec3(0, 0.0, 1), vec2up)
	};

	unsigned int indices[6] = {  // note that we start from 0!
	0, 2, 1   // first triangle
	};

	Mesh();

	unsigned int vao();
	unsigned int vertexCount();


	void uploadToGPU();

	void draw();

};

