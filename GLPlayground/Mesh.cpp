#include "Mesh.h"

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include "Shader.h"


#define BUFFER_OFFSET(i) ((void*)(i))

std::vector<Mesh*> Mesh::s_uploadedMeshes;

VertexAttribute::VertexAttribute(glm::vec3 position, glm::vec3 color, glm::vec2 uv)
{
	this->position = position;
	this->color = color;
	this->uv = uv;
}

Mesh::Mesh()
{
	c_vao = 0;
	c_vertexCount = 0;
}

unsigned int Mesh::vao()
{
	return c_vao;
}

unsigned int Mesh::vertexCount()
{
	return c_vertexCount;
}

void Mesh::uploadToGPU()
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	unsigned int vbo;
	glGenBuffers(1, &vbo);


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * attributes.size(), attributes.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices.data(), GL_STATIC_DRAW);

	c_vao = vao;

}


void Mesh::draw()
{

	//std::cout << "Mesh: " << c_vao << std::endl;

	glBindVertexArray(c_vao);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

}


void Mesh::deleteAllVAOs()
{
	for (Mesh* mesh : s_uploadedMeshes)
	{

		glDeleteVertexArrays(1, &(mesh->c_vao));
	}
}

Mesh* Mesh::gen_quad(float size)
{
	size *= 0.5f;
	std::vector<VertexAttribute> vertices = {
		VertexAttribute((vec3left + vec3up) * size, vec3one, vec2up),
		VertexAttribute((vec3right + vec3up) * size, vec3one, vec2up + vec2right),
		VertexAttribute((vec3left + vec3down) * size, vec3one, vec2zero),
		VertexAttribute((vec3right + vec3down) * size, vec3one, vec2right)
	};

	std::vector<unsigned int> indices = {
		0, 2, 1,
		1, 2, 3
	};

	Mesh* mesh = new Mesh();
	mesh->attributes = vertices;
	mesh->indices = indices;
	mesh->c_vertexCount = vertices.size();

	return mesh;

}

