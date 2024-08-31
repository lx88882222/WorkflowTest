# 设置最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(3DConstructer VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加源文件
# 假设你的源文件在 src 目录下
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 添加可执行文件
add_executable(3DConstructer ${SOURCES})

# 包含头文件目录
# 假设你的头文件在 src 目录下
include_directories(src)