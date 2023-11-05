```markdown
# three_d

A simple OpenGL project that opens a window and sets up an OpenGL context using GLFW.

## Description

This project is a starting point for anyone looking to get into 3D graphics programming. It sets up a window and an OpenGL context using the GLFW library.

## Build Instructions

### Prerequisites

- CMake
- A C++ compiler (e.g., GCC, Clang, MSVC)
- GLFW

### macOS

1. Install Homebrew (if not already installed):

```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

2. Install GLFW using Homebrew:

```sh
brew install glfw
```

3. Navigate to the project directory and create a build directory:

```sh
cd path/to/three_d
mkdir build && cd build
```

4. Generate the build configuration with CMake:

```sh
cmake ..
```

5. Build the project:

```sh
cmake --build .
```

### Windows

1. Install CMake and a C++ compiler (if not already installed).
2. Install GLFW. You can download pre-compiled binaries or use a package manager like vcpkg.
3. Open a command prompt or PowerShell in the project directory.
4. Create a build directory:

```sh
mkdir build && cd build
```

5. Generate build configuration files with CMake. Specify the generator if necessary:

```sh
cmake -G "MinGW Makefiles" ..
# or, for Visual Studio
cmake -G "Visual Studio 16 2019" -A x64 ..
```

6. Build the project:

```sh
cmake --build .
```

### Raspberry Pi (Linux)

1. Install the necessary packages:

```sh
sudo apt-get update
sudo apt-get install cmake xorg-dev libglfw3-dev
```

2. Navigate to the project directory and create a build directory:

```sh
cd path/to/three_d
mkdir build && cd build
```

3. Generate the build configuration with CMake:

```sh
cmake ..
```

4. Build the project:

```sh
cmake --build .
```

## Usage

After building the project, you can run the executable generated in the `build` directory.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
```

Replace `path/to/three_d` with the actual path to your project directory. 
