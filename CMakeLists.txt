cmake_minimum_required(VERSION 3.25.1)
project("SortingVisualization")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (THIRD_PARTY_DIR third_party)

add_subdirectory(${THIRD_PARTY_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)