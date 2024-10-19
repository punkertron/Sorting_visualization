project(imgui)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

set(IMGUI_DIR imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/${IMGUI_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/${IMGUI_DIR}/backends
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(imgui PRIVATE ${SDL2_LIBRARIES} OpenGL::GL)