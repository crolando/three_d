#include "main.hpp"
#include "shader_loader.h"
#ifdef USE_OPENGLES
	#define GLFW_INCLUDE_ES3
#endif
#include <GLFW/glfw3.h>

// Constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Hello World";
const char* VERT_SHADER_PATH = "../quad.vert";
const char* FRAG_SHADER_PATH = "../quad.frag";
const char* MANDLEBROT_FRAG_SHADER_PATH = "../mandlebrot.frag";

// Function declarations
bool initializeGlfw();
bool initializeGlew();
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath);
void setupQuadVAO(const float* vertices, size_t size, GLuint &quadVAO, GLuint &quadVBO);
void glfwErrorCallback(int error, const char* description);
void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

// Global var (how callbacks communicate back to this scope)
float zoom;
float panX;
float panY;

// Full-screen quad vertices
float quadVertices[] = {
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};



int main(void) {
    
    if (!initializeGlfw()) {
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    #ifndef USE_OPENGLES
		if(!initializeGlew()) {
			glfwTerminate();
			return -1;
		}
    #endif
    
    glfwSetScrollCallback(window, scrollCallBack);
    glfwSetKeyCallback(window, keyCallBack);
    
    GLuint shaderPrograms[2];
    GLuint shaderProgram = createShaderProgram(VERT_SHADER_PATH, FRAG_SHADER_PATH);
    if (shaderProgram == 0) {
       glfwTerminate();
       return -1;
    }
    shaderPrograms[0] = shaderProgram;
    
    shaderProgram = createShaderProgram(VERT_SHADER_PATH, MANDLEBROT_FRAG_SHADER_PATH);
    if (shaderProgram == 0) {
       glfwTerminate();
       return -1;
    }
    shaderPrograms[1] = shaderProgram;
    
    GLuint quadVAO, quadVBO;
    setupQuadVAO(quadVertices, sizeof(quadVertices), quadVAO, quadVBO);
    
    if (quadVAO == 0) {
       glfwTerminate();
       return -1;
    }
    
    // Init zoom and pan uniforms
    zoom = 1.0f;
    struct uivec2 {unsigned int x; unsigned int y; };
    uivec2 resolution = {WINDOW_WIDTH, WINDOW_HEIGHT};

    GLuint zoomLoc = glGetUniformLocation(shaderProgram, "zoom");
    GLuint panLoc = glGetUniformLocation(shaderProgram, "pan");
    GLuint resolutionLoc = glGetUniformLocation(shaderProgram, "resolution");

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        
        std::string title = std::to_string(zoom) + " " + std::to_string(panX) + " " + std::to_string(panY);
        
        glfwSetWindowTitle(window,title.c_str());
        
        glUseProgram(shaderPrograms[1]);
        
        glUniform1f(zoomLoc, zoom);
        glUniform2f(panLoc, panX, panY);
        glUniform2f(resolutionLoc, resolution.x, resolution.y);
        
        // Render here
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    
    // Clean up VAO and VBO objects
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);

    glfwTerminate();
    return 0;
}

bool initializeGlfw() {
    glfwSetErrorCallback(glfwErrorCallback);
    
    // Initialize the library
    if (!glfwInit()) {
        return false;
    }
    #ifdef USE_OPENGLES
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // This is required on Mac
    #else 
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // This is required on Mac
    #endif
    return true;
}
#ifndef USE_OPENGLES
	bool initializeGlew() {
		// Initialize GLEW
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			// Problem: glewInit failed, something is seriously wrong.
			std::cerr << "Error with glewInit: " << glewGetErrorString(err) << std::endl;
			return false;
		}
		return true;
	}
#endif
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath) {
        
    // Compile Shader from File
    GLuint vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    
    // Create a shader program and attach the shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    
    // Detach and delete shaders as they are no longer needed
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
    // Use the shader program
    glUseProgram(shaderProgram);

    return shaderProgram;
}

void setupQuadVAO(const float* vertices, size_t size, GLuint &quadVAO, GLuint &quadVBO) {
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // Texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Unbind the VAO to avoid accidental modification
    glBindVertexArray(0);
    // Unbind the VBO after unbinding the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error callback called. Description is: " << std::endl;
    std::cerr << description << std::endl;
}

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
    // Use yoffset to zoom in/out
    float zoomSpeed = 1.0;
    zoom = zoom + (yoffset * 0.001);
    
    //zoom += static_cast<float>(yoffset) * zoomSpeed; // zoomSpeed controls the sensitivity
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    float panSpeed = 0.01 * zoom;
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                panY -= panSpeed; // Move up
                break;
            case GLFW_KEY_DOWN:
                panY += panSpeed; // Move down
                break;
            case GLFW_KEY_LEFT:
                panX += panSpeed; // Move left
                break;
            case GLFW_KEY_RIGHT:
                panX -= panSpeed; // Move right
                break;
        }
    }
}
