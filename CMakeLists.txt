cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(D:/vcpkg/installed/x64-windows/include)
link_directories(D:/vcpkg/installed/x64-windows/lib)

project(GameOfLife)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
    
file(GLOB SOURCES source/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_include_directories(${PROJECT_NAME} PRIVATE include)