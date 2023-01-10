#pragma once
#include "Includes.h"
#include "Enums.h"

// general
string fileToShaderString(string filename);

// shaders
int loadShader(string sourceFile, string shaderType, unsigned int& shaderObject);
int loadAndLinkShaders(string vertexShaderSource, string fragmentShaderSource, unsigned int& shaderProgram);

// texture
void generateTexture(string src, unsigned int& texture);

// logging
void LogInfo(string log);
void LogWarn(string log);