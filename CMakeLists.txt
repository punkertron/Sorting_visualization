cmake_minimum_required(VERSION 3.25.1)
project("SortingVisualization")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (THIRD_PARTY_DIR third_party)

add_subdirectory(${THIRD_PARTY_DIR})

set(SOURCE_DIR src)
add_executable(${PROJECT_NAME}
    ${SOURCE_DIR}/main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)