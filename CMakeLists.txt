cmake_minimum_required(VERSION 3.10) 
project(modern)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-10")

# setting paths for libraries and executable outputs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

FIND_PACKAGE(GLEW)

# setting path to include files 
include_directories( 
    ${CMAKE_SOURCE_DIR}/include 
    $ENV{HOME}/.local/include 
) 

find_library(GLFW_LIB glfw)

message("-- GLFW Library ${GLFW_LIB}")

set(LIBS ${LIBS} ${GLEW_LIBRARIES})

add_executable(application ${CMAKE_SOURCE_DIR}/src/application.cpp)
target_link_libraries(application ${GLFW_LIB} ${GLEW_LIBRARIES} -lGL)
target_link_options(application PUBLIC "LINKER:-rpath,/usr/lib64")

