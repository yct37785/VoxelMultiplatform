#pragma once
// common headers
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include <time.h>       /* time */
#include <iterator>
#include <bitset>
#include <iomanip>
#include <random>
#include <map>
// Core C++, OpenGL, texture and any other platform specific libs
#ifdef PLATFORM_WINDOWS
// memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// OpenGL specific
#include <glad/glad.h>  // !include before GLFW!
#include <GLFW/glfw3.h>
#elif PLATFORM_ANDROID
// OpenGL ES and GL context
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <JNIHelper.h>
#include <GLContext.h>
#elif __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>	// replaces GLAD
#include <GLFW/glfw3.h>
#endif
// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
// defines
#define PI 3.141592653589793
static int windowsWidth = 1280;
static int windowsHeight = 720;
#ifdef PLATFORM_WINDOWS
const static string assetsPath = "../../shared/Assets";
const static string shaderspath = "../../shared/Shaders";
#elif PLATFORM_ANDROID
const static string assetsPath = "Assets";
const static string shaderspath = "Shaders";
#elif __EMSCRIPTEN__
const static string assetsPath = "LearnOpenGL/Assets";
const static string shaderspath = "LearnOpenGL/Shaders";
#endif

// enums
enum MESH_TYPES {
	// primitives
	MESH_CUBE,
	MESH_SPHERE,
	MESH_LINE,
	MESH_QUAD_INFINITE_FLOOR,
	// OBJs
	MESH_TOTAL
};

enum TEX_TYPES {
	// bg
	TEX_FLOOR_TILES,
	TEX_FLOOR_TILES_SPECULAR,
	// face
	TEX_WOODEN_CRATE_FACE,
	TEX_WOODEN_CRATE_FACE_SPECULAR,
	TEX_TOTAL
};

enum MAT_TYPES {
	MAT_WHITE_COLOR,
	MAT_RED_COLOR,
	MAT_GREEN_COLOR,
	MAT_BLUE_COLOR,
	MAT_WOODEN_CRATE,
	MAT_FLOOR_TILES,
	MAT_TOTAL
};

enum SHADER_TYPES {
	SHADER_LIGHT_MAP,
	SHADER_COLOR,
	SHADER_TOTAL
};

enum INPUT_TYPES {
	INPUT_FWD,
	INPUT_BWD,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_UP,
	INPUT_DW,
	INPUT_ENABLE_WIREFRAME,
	INPUT_DISABLE_WIREFRAME,
	INPUT_QUIT,
	INPUT_TOTAL
};

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