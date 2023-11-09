// shader_loader.cpp
#include "shader_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string readShaderFile(const char* shaderPath) {
    std::string shaderCode;
    std::ifstream shaderFile;

    // Ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open file
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;

        // Read file's buffer contents into stream
        shaderStream << shaderFile.rdbuf();

        // Close file handler
        shaderFile.close();

        // Convert stream into string
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    return shaderCode;
}

GLuint compileShader(const char* shaderPath, GLenum shaderType) {
    std::cout << "About to compile the shader..." << std::endl;
    std::string shaderCode = readShaderFile(shaderPath);
    const char* shaderCodeCStr = shaderCode.c_str();

    // Create the shader object
    GLuint shader = glCreateShader(shaderType);
    std::cout << "glCreateShader returned sucessfully" << std::endl;
    glShaderSource(shader, 1, &shaderCodeCStr, NULL);
    glCompileShader(shader);

    std::cout << "Shader object created" << std::endl;
    
    // Check for shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << shaderPath << " -> " << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog  << std::endl;
    } else {
        std::cout << "Shader Compiled" << std::endl;
    }

    return shader;
}
