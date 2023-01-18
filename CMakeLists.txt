cmake_minimum_required(VERSION 3.24)
project(AbstractGeometry)

set(CMAKE_CXX_STANDARD 17)

find_package(GLUT)
include_directories(${GLUT_INCLUDE_DIRS})

add_executable(AbstractGeometry main.cpp)

target_link_libraries(AbstractGeometry ${GLUT_LIBRARIES} /lib/x86_64-linux-gnu/libGL.so.1)