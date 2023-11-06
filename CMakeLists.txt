cmake_minimum_required(VERSION 3.11)
project(three_d)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the required packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

if(UNIX AND NOT APPLE)
    # Raspberry Pi
    add_definitions(-DUSE_OPENGLES)
elseif(APPLE)
    # Mac
    find_package(GLEW REQUIRED CONFIG)
else()
    # Windows - untested
    find_package(GLEW REQUIRED)
endif()

# Add the executable with main.cpp and shader_loader.cpp
add_executable(${PROJECT_NAME} main.cpp shader_loader.cpp)

# Link with the libraries
target_link_libraries(${PROJECT_NAME} glfw)
if(UNIX AND NOT APPLE)
    # Link against OpenGL ES for Raspberry Pi
    target_link_libraries(${PROJECT_NAME} GLESv2)
else()
    # Link against OpenGL for desktop systems
    if(OpenGL_GL_PREFERENCE STREQUAL "GLVND")
        target_link_libraries(${PROJECT_NAME} OpenGL::OpenGL)
    elseif(OpenGL_GL_PREFERENCE STREQUAL "LEGACY")
        target_link_libraries(${PROJECT_NAME} OpenGL::GL)
    endif()
endif()

if(GLEW_FOUND)
    target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
endif()

# Include directories for GLEW and OpenGL
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()
