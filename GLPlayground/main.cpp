#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <string>

#include "glmath.h"

#include "main.h"

#include "io.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Entity.h"

#include "MeshRenderer.h"
#include "Camera.h"


std::vector<Entity*> g_entities;


int w = 1600;
int h = 900;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


Entity* createEntity(std::string name = "Auto entity " + g_entities.size())
{
	Entity* e = new Entity(name);
	g_entities.push_back(e);
	return e;
}


int main() {


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	GLFWwindow* window = glfwCreateWindow(w, h, "LearnOpenGL", NULL, NULL);


	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, w, h);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader::compileAll();
	Texture::loadAll();

	Mesh* m = Mesh::gen_quad();
	m->uploadToGPU();

	Texture* tex = Texture::get("res/bricks.jpg");
	tex->use();


	Entity* camEntity = createEntity();
	Camera* cam = camEntity->addComponent<Camera>();

	Entity* e = createEntity();
	MeshRenderer* r = e->addComponent<MeshRenderer>();

	r->mesh = m;
	r->shader = Shader::get("test");
	r->texture = tex;


	float lastTime = glfwGetTime();
	float now = 0.0f;

	float dt = 0.1f;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		for (auto en : g_entities)
		{
			en->update(dt);
		}


		cam->render();

		glfwSwapBuffers(window);
		glfwPollEvents();


		now = glfwGetTime();
		dt = now - lastTime;
		lastTime = now;

	}

	Mesh::deleteAllVAOs();


	glfwTerminate();
	return 0;

}
