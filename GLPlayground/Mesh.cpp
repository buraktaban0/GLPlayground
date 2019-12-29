#include "Mesh.h"

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include "Shader.h"


#define BUFFER_OFFSET(i) ((void*)(i))


VertexAttribute::VertexAttribute(glm::vec3 position, glm::vec3 color, glm::vec2 uv)
{
	this->position = position;
	this->color = color;
	this->uv = uv;
}

Mesh::Mesh()
{

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * c_vertexCount, attributes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	c_vao = vao;

}


void Mesh::draw()
{

	Shader shader = Shader::get("test");
	shader.use();


	glUniform1i(glGetUniformLocation(shader.programID(), "tex"), 0);

	glBindVertexArray(c_vao);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

}

