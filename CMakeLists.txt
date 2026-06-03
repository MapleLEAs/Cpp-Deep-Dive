cmake_minimum_required(VERSION 3.16)   # CMake 最低版本要求
project(CppDeepDive)                   # 项目名

set(CMAKE_CXX_STANDARD 17)             # 用 C++17 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # 编译器不支持 17 就直接报错

include_directories(${CMAKE_SOURCE_DIR}/include)  # 让编译器能找到你的 .hpp

add_executable(test_util tests/test_util.cpp)     # 把 test_util.cpp 编译成可执行文件