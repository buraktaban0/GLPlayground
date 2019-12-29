#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

class MeshRenderer : public Component
{
	

public:


	MeshRenderer();

	Mesh* mesh;
	Texture* texture;
	Shader* shader;


	std::string name() const;


	void start() const;


	void update(float dt) const;


};

