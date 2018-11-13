cmake_minimum_required(VERSION 3.12)
project(ogl)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
set(${CMAKE_CXX_FLAGS} -lglfw -lglew -lgl -framework OpenGL)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLFW_INCLUDE_ES3})
link_libraries(${GLFW_LIBRARY})

include_directories(${OpenGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})


include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ogl src/main.cpp src/ShaderUtils.h)
target_link_libraries(ogl glfw ${GLEW_LIBRARIES})