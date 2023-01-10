#pragma once
#include "Scene.h"

/*
* Very basic triangle draw. To learn about the basics of opengl.
*/
class SceneBasicLighting : public Scene
{
	// an object
	const static int total_gameObjects = 5;
	GameObject cubes[total_gameObjects];
	GameObject lightBulb0;
	glm::vec3 light_0_color;

	// shader
	Shader shaderProgram, lightSourceShaderProgram;

	// camera
	Camera camera;

	// transformation
	glm::mat4 view, projection;

	void InitObjects();
	void UpdateTransformation(float deltaTime);
	void UpdateViewMatrix();

public:
	SceneBasicLighting();
	~SceneBasicLighting();

	void Init();
	void Update(GLFWwindow* window, float deltaTime);
	void Draw();
	
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};