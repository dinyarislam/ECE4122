cmake_minimum_required(VERSION 2.8)

# set the project name
project(ServerApp)

set(EXECUTABLE_OUTPUT_PATH ../)

# add the executable
add_executable(ServerApp ./tcpServer.cpp)

target_link_libraries(ServerApp PUBLIC 
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-window.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-system.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-graphics.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-network.so>
)



target_include_directories(ServerApp PUBLIC
                          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/"
                          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/"
                          )