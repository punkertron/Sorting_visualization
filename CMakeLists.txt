cmake_minimum_required(VERSION 3.25.1)
project("SortingVisualization")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRD_PARTY_DIR third_party)

set(CMAKE_CXX_FLAGS "-g3 -fsanitize=thread")

add_subdirectory(${THIRD_PARTY_DIR})

set(SOURCE_DIR src)
set(ALGORITHMS_DIR sortingAlgorithms)
add_executable(${PROJECT_NAME}
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/SDL2OpenGL2Creator.cpp
    ${SOURCE_DIR}/ImGuiSDL2OpenGL2Manager.cpp
    ${SOURCE_DIR}/Controller.cpp
    ${SOURCE_DIR}/SortingManager.cpp
    ${SOURCE_DIR}/Controller.cpp
    ${SOURCE_DIR}/${ALGORITHMS_DIR}/BubbleSort.cpp
    ${SOURCE_DIR}/${ALGORITHMS_DIR}/InsertionSort.cpp
    ${SOURCE_DIR}/${ALGORITHMS_DIR}/MergeSort.cpp
    ${SOURCE_DIR}/${ALGORITHMS_DIR}/QuickSort.cpp
    ${SOURCE_DIR}/${ALGORITHMS_DIR}/HeapSort.cpp
    ${SOURCE_DIR}/${ALGORITHMS_DIR}/ShellSort.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)