cmake_minimum_required(VERSION 3.24)
project(AbstractGeometry)

set(CMAKE_CXX_STANDARD 17)

find_package(GLUT)
find_package(OpenGL)
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(AbstractGeometry main.cpp)

target_link_libraries(AbstractGeometry ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})