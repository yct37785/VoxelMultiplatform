#pragma once
#include "../Utility.h"

class Shader
{
	unsigned int shaderID;

public:
	Shader();
	~Shader();

	void Init(string vertexShaderSource, string fragmentShaderSource);
	void activateShader();

	void setUniform1f(string label, float value);
	void setUniform1i(string label, int value);
	void setUniform3fv(string label, glm::vec3 value);
	void setUniformMatrix4fv(string label, glm::mat4& value);
};

