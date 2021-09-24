#cmake_minimum_required(VERSION 3.16)
#project(codecamp)
#set(CMAKE_CXX_STANDARD 17)


################################
# setting path to include files 
################################

include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include 
) 

######################
# compiled libraries
######################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

message(STATUS "${CMAKE_SOURCE_DIR}")
message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}")

FIND_PACKAGE(GLEW)
message("-- GLEW Library ${GLEW_LIBRARIES}")

find_library(GLFW_LIB glfw)
message("-- GLFW Library ${GLFW_LIB}")

set(LIBS ${LIBS} ${GLEW_LIBRARIES})

add_library(shader STATIC shader.cpp)
target_link_libraries(shader ${GLEW_LIBRARIES} -lGL)

add_library(vbo STATIC vbo.cpp)
target_link_libraries(vbo ${GLEW_LIBRARIES} -lGL)

add_executable(lesson lesson.cpp ${shader} ${vbo})
target_link_libraries(lesson ${GLFW_LIB} ${GLEW_LIBRARIES} -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl shader vbo)
target_link_options(lesson PUBLIC "LINKER:-rpath,/usr/lib64")

