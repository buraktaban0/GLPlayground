#pragma once

#include "Component.h"

#include "glmath.h"

class Transform : public Component
{

public:

	glm::vec3 position;

	Transform();

	std::string name() const;

	void start() const;

	void update(float dt) const;

	void translate(glm::vec3 delta);

	glm::mat4 modelMatrix();

};

