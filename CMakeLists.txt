# 设定最低 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的语言
project(project-HuffPlus)

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置项目包含的头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 将源码文件列入 CMake 项目中
add_executable(project-HuffPlus
    src/main.cpp
    src/Huffman.cpp
)