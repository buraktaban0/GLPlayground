#include "Transform.h"


Transform::Transform()
{
	position = vec3zero;
}

std::string Transform::name() const
{
	return "Transform";
}

void Transform::start() const
{

}

void Transform::update(float dt) const
{
}

void Transform::translate(glm::vec3 delta)
{
	position += delta;
}

glm::mat4 Transform::modelMatrix()
{
	return glm::translate(glm::mat4(1.0f), position);
}
