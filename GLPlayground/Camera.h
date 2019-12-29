#pragma once

#include "Component.h"
#include <vector>
#include "MeshRenderer.h"

class Camera : public Component
{

	static std::vector<const MeshRenderer*> s_meshRenderers;

public:


	std::string name() const;

	void start() const;

	void update(float dt) const;
	
	void render();




	static void addRenderer(const MeshRenderer* r);


};

