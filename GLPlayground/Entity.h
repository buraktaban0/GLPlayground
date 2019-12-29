#pragma once
#include <string>
#include <vector>

#include <iostream>

class Component;
class Transform;

class Entity
{

	std::string c_name;

	std::vector<Component*> c_components;

public:

	Transform* transform;

	Entity(std::string name);

	void update(float dt);

	std::string name();

	void listComponents();

	template<typename T>
	T* addComponent()
	{
		T* comp = new T();
		comp->owner = this;
		comp->start();
		c_components.push_back(comp);
		return comp;
	}

	template<typename T>
	T* getComponent()
	{

		for (Component* comp : c_components)
		{
			T* child = dynamic_cast<T*>(comp);

			if (child != NULL)
			{
				return child;
			}

		}
		return NULL;

	}

	template<typename T>
	void removeComponent()
	{
		int index = -1;
		for (int i = 0; i < c_components.size(); i++)
		{
			T* child = dynamic_cast<T*>(c_components[i]);
			if (child != NULL)
			{
				index = i;
				break;
			}

		}

		if (index >= 0)
		{
			c_components.erase(c_components.begin() + index);
		}

	}

};

