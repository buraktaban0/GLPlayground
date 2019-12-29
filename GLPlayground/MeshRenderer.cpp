#include "MeshRenderer.h"
#include <iostream>


#include "Camera.h"

MeshRenderer::MeshRenderer()
{
	mesh = NULL;
	shader = NULL;
	texture = NULL;
}

std::string MeshRenderer::name() const
{
	return "Mesh Renderer";
}

void MeshRenderer::start() const
{
	Camera::addRenderer(this);
}

void MeshRenderer::update(float dt) const
{

}



