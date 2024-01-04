# Cuphead Clone Project

### **Welcome to the Cuphead Clone project! This is one of my first significant projects in C++, and I'm excited to share it with you. I've dedicated 3.5 months to bring this game to life, inspired by the challenging and visually stunning Cuphead.**

## Building a project for Windows

1. Download and install [Git](https://git-scm.com/download/win ) from the official website
2. Download and install [CMake](https://cmake.org/download) from the official website
3. Скачайте и установите [Clang](https://releases.llvm.org/download.html) для Windows с официального сайта LLVM
4. Add the path to the Clang executable files to the PATH variable.
5. Download and install [Ninja](https://ninja-build.org/download.html ) for Windows from the official website
6. Add the path to the Ninja executable files to the PATH variable.
7. Download and install [vcpkg](https://github.com/microsoft/vcpkg ) from the official repository on GitHub
8. Clone the project repository using Git
```bash
git clone git@github.com:kub78/cuphead.git
```
### Go to the project directory
### Use the command
```bash
vcpkg install --triplet x64-windows-release
``` 
### Use the command
```bash
cmake -G Ninja -B build –D CMAKE_BUILD_TYPE=Release –D CMAKE_CXX_COMPILER=clang++
```
### Use the command 
 ```bash
cmake --build build
``` 
### Go to the build directory and run cuphead.exe.

## Building a project for Linux

### Install the necessary packages using the package manager of your distribution, for example, for Ubuntu:
    - sudo apt-get install git cmake clang ninja-build
    - sudo apt-get install libboost-all-dev
    - sudo apt-get install libsfml-dev
    - sudo apt-get install nlohmann-json3-dev
### Clone the project repository using Git
```bash
git clone git@github.com:kub78/cuphead.git
```
### Go to the project directory

### Use the command
```bash
cmake -G Ninja -B build -D CMAKE_BUILD_TYPE=Release
```
### Use the command
```bash
cmake --build build
```
### Go to the build directory and run cuphead


## Feel free to explore and enjoy the Cuphead game clone! If you encounter any issues or have suggestions, please don't hesitate to open an issue on the project's GitHub repository.

