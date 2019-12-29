#pragma once

#include <string>

class Entity;

class Component
{

public:

	Entity* owner;

	virtual std::string name() const = 0;

	virtual void start() const = 0;

	virtual void update(float dt) const = 0;

};

