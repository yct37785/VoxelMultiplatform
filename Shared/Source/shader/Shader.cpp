#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
}

Shader::~Shader()
{
	glDeleteShader(shaderID);
}

void Shader::Init(string vertexShaderSource, string fragmentShaderSource)
{
	loadAndLinkShaders(vertexShaderSource, fragmentShaderSource, shaderID);
}

void Shader::activateShader()
{
	glUseProgram(shaderID);
}

void Shader::setUniform1f(string label, float value)
{
	// glUniform1f doesn't work on Android
	glUniform1f(glGetUniformLocation(shaderID, label.c_str()), value);
}

void Shader::setUniform1i(string label, int value)
{
	glUniform1i(glGetUniformLocation(shaderID, label.c_str()), value);
}

void Shader::setUniform3fv(string label, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(shaderID, label.c_str()), 1, glm::value_ptr(value));
}

void Shader::setUniformMatrix4fv(string label, glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, label.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}