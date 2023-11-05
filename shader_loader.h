// shader_loader.h
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <GL/glew.h>
#include <string>

std::string readShaderFile(const char* shaderPath);
GLuint compileShader(const char* shaderPath, GLenum shaderType);

#endif // SHADER_LOADER_H
