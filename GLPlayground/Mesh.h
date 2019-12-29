#pragma once

#include "glmath.h"

#include <vector>

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

	unsigned int c_vertexCount;


	static std::vector<Mesh*> s_uploadedMeshes;


public:


	/**
	float vertices[12] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
	};
	*/


	std::vector<VertexAttribute> attributes;

	std::vector<unsigned int> indices;

	Mesh();

	unsigned int vao();
	unsigned int vertexCount();


	void uploadToGPU();

	void draw();


	static void deleteAllVAOs();

	static Mesh* gen_quad(float size = 1.0f);


};

