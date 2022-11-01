cmake_minimum_required(VERSION 3.22.1)

project(Completed)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC CONFIGURE DEPENDS "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

