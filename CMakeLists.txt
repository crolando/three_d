cmake_minimum_required(VERSION 3.0)
project(three_d)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the required packages
find_package(glfw3 REQUIRED)
if(APPLE)
	find_package(GLEW REQUIRED CONFIG)
else()
	find_package(GLEW REQUIRED)
endif()

# Add the executable with main.cpp and shader_loader.cpp
add_executable(${PROJECT_NAME} main.cpp shader_loader.cpp)

# Link against the GLFW and GLEW libraries
target_link_libraries(${PROJECT_NAME} glfw GLEW::GLEW)

# Include directories for GLEW
include_directories(${GLEW_INCLUDE_DIRS}) # Add this line to include GLEW headers

# If you have other libraries to link (like OpenGL), you can do so like this:
# find_package(OpenGL REQUIRED)
# target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})
