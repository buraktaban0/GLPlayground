#include "Entity.h"
#include "Transform.h"

Entity::Entity(std::string name)
{
	c_name = name;

	transform = new Transform();
}

void Entity::update(float dt)
{
	transform->translate(dt * vec3right * 0.2f);

	for (auto c : c_components)
	{
		c->update(dt);
	}
}


std::string Entity::name()
{
	return c_name;
}



void Entity::listComponents()
{
	std::string s = "";
	for (auto c : c_components)
	{
		s += c->name();
		s += "\r\n";
	}

	std::cout << s;
}

