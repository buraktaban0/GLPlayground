#include "Camera.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include "Entity.h"
#include "Transform.h"

std::vector<const MeshRenderer*> Camera::s_meshRenderers;

std::string Camera::name() const
{
	return "Camera";
}

void Camera::start() const
{
}

void Camera::update(float dt) const
{
}



void Camera::render()
{
	//std::cout << s_meshRenderers.size() << std::endl;

	for (const MeshRenderer* r : s_meshRenderers)
	{

		r->shader->use();

		glm::mat4 modelMat = r->owner->transform->modelMatrix();

		r->shader->setModelMat(modelMat);

		r->texture->use();

		r->mesh->draw();
	}

}



void Camera::addRenderer(const MeshRenderer* r)
{
	s_meshRenderers.push_back(r);
}