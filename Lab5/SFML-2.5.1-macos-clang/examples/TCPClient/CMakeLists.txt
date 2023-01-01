cmake_minimum_required(VERSION 2.8)

# set the project name
project(ClientApp)

set(EXECUTABLE_OUTPUT_PATH ../)

# add the executable
add_executable(ClientApp ./tcpClient.cpp)

target_link_libraries(ClientApp PUBLIC 
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-window.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-system.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-graphics.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-network.so>
)



target_include_directories(ClientApp PUBLIC
                          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/"
                          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/"
                          )