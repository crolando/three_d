// shader_loader.h
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#ifdef USE_OPENGLES
	#include <GLES3/gl3.h>
#else
	#include <GL/glew.h>
#endif

#include <string>

std::string readShaderFile(const char* shaderPath);
GLuint compileShader(const char* shaderPath, GLenum shaderType);

#endif // SHADER_LOADER_H
