cmake_minimum_required(VERSION 3.15)
project(C__)

set(CMAKE_CXX_STANDARD 11)

# 预编译宏
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DZENGLW")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPI")

add_executable(C__ main.cpp a.h a.cpp mainc.c b.c b.h cplus.h oopTest.cpp oopTest.h)
