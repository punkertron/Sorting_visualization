#include "ImGuiSDL2OpenGL2Manager.hpp"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"

ImGuiSDL2OpenGL2Manager::ImGuiSDL2OpenGL2Manager(SDL_Window* window, SDL_GLContext glContext):
    window(window), glContext(glContext)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL2_Init();
}

ImGuiSDL2OpenGL2Manager::~ImGuiSDL2OpenGL2Manager()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

bool ImGuiSDL2OpenGL2Manager::handleExit()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            return true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            return true;
    }
    return false;
}

void ImGuiSDL2OpenGL2Manager::updateData(SettingsData& settingsData)
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(450, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("Parameters", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

    ImGui::Text("\nWelcome to the Settings!\n\n\n\n");

    ImGui::InputInt("Number of elements", &settingsData.numberOfElements);
    ImGui::SliderInt("Speed", &settingsData.speed, 1, 5);

    ImGui::Text("\n\nSelect algorithms:");
    ImGui::Checkbox("Bubble sort", &settingsData.isBubbleSortSelected);
    ImGui::Checkbox("Insertion sort", &settingsData.isInsertionSortSelected);
    ImGui::Checkbox("Quick sort", &settingsData.isQuickSortSelected);
    ImGui::Checkbox("Merge sort", &settingsData.isMergeSortSelected);
    ImGui::Checkbox("Heapsort", &settingsData.isHeapSortSelected);
    ImGui::Checkbox("Shellsort", &settingsData.isShellSortSelected);
    ImGui::Text("\n");
    
    {    
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(18, 195, 73));
        ImGui::SetCursorPosX(100);
        ImGui::Button("Run the animation");
        ImGui::PopStyleColor(1);
    }

    ImGui::End();
}

void ImGuiSDL2OpenGL2Manager::render()
{
    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}
