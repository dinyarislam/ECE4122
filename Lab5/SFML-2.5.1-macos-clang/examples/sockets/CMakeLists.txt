cmake_minimum_required(VERSION 2.8)

# set the project name
project(SocketApp)

set(EXECUTABLE_OUTPUT_PATH ../)

# add the executable
add_executable(SocketApp ./Sockets.cpp
			 ./TCP.cpp
			 ./UDP.cpp)

target_link_libraries(SocketApp PUBLIC 
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-window.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-system.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-graphics.so>
                                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/libsfml-network.so>
)



target_include_directories(SocketApp PUBLIC
                          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/"
                          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/"
                          )