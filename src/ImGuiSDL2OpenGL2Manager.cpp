#include "ImGuiSDL2OpenGL2Manager.hpp"

#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl2.h"

static const int PARAMETERS_WINDOW_WIDTH = 350;
static const int SLIDER_BAR_WIDTH = 200;

ImGuiSDL2OpenGL2Manager::ImGuiSDL2OpenGL2Manager(SDL_Window* window, SDL_GLContext glContext) :
    window(window), glContext(glContext)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

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

void ImGuiSDL2OpenGL2Manager::startRender()
{
    start = SDL_GetTicks();
}

bool ImGuiSDL2OpenGL2Manager::handleExit()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            return true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(window))
            return true;
    }
    return false;
}

void ImGuiSDL2OpenGL2Manager::updateSettings(SettingsData& settingsData)
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(PARAMETERS_WINDOW_WIDTH, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("Parameters", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

    ImGui::Text("\nWelcome to the Settings!\n\n\n\n");

    ImGui::SetNextItemWidth(SLIDER_BAR_WIDTH);
    ImGui::SliderInt("Number of elements", &settingsData.numberOfElements, 1, 500);
    ImGui::SetNextItemWidth(SLIDER_BAR_WIDTH);
    ImGui::SliderInt("Speed", &settingsData.speed, 1, 100);

    ImGui::Text("\n\nSelect algorithms:");
    ImGui::Checkbox("Bubble sort", &settingsData.isBubbleSortSelected);
    ImGui::Checkbox("Insertion sort", &settingsData.isInsertionSortSelected);
    ImGui::Checkbox("Quick sort", &settingsData.isQuickSortSelected);
    ImGui::Checkbox("Merge sort", &settingsData.isMergeSortSelected);
    ImGui::Checkbox("Heapsort", &settingsData.isHeapSortSelected);
    ImGui::Checkbox("Shellsort", &settingsData.isShellSortSelected);
    ImGui::Text("\n");

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(18, 195, 73));
    ImGui::SetCursorPosX(100);
    settingsData.isStarted = ImGui::Button("Run the animation");
    ImGui::PopStyleColor(1);

    ImGui::End();
}

void ImGuiSDL2OpenGL2Manager::updateVisualizationArea(std::unordered_map<const char*, const std::vector<int>*> sortedData)
{
    ImGui::SetNextWindowPos(ImVec2(PARAMETERS_WINDOW_WIDTH, 0));  // Position right after the menu
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - PARAMETERS_WINDOW_WIDTH, ImGui::GetIO().DisplaySize.y));
    ImGui::Begin("Visualization Area", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    float sizeOnePanel =
        ImGui::GetContentRegionAvail().y / sortedData.size() - 6;  // -6 because we need some more space for one panel
    for (const auto& [algoName, algoData] : sortedData) {
        ImGui::BeginChild(algoName, ImVec2(0, sizeOnePanel), true);
        ImGui::Text(algoName);
        // Visualization Drawing Code
        int max_val = algoData->size() - 1;

        ImVec2 content_region = ImGui::GetContentRegionAvail();

        float bar_width = content_region.x / static_cast<float>(algoData->size());

        for (size_t i = 0; i < algoData->size(); ++i) {
            float bar_height = (static_cast<float>((*algoData)[i]) / max_val) * content_region.y;

            ImVec2 p0 = ImGui::GetCursorScreenPos();
            p0.y += content_region.y;
            ImVec2 p1 = ImVec2(p0.x + bar_width - 2, p0.y - bar_height);

            ImU32 color = IM_COL32((algoName[0] * 10) % 256, (algoName[1] * 10) % 256, (algoName[2] * 10) % 256, 255);

            // Draw filled rectangle (bar)
            ImGui::GetWindowDrawList()->AddRectFilled(p0, p1, color);

            // Move cursor to the next bar position
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + bar_width);
        }
        ImGui::EndChild();
        ImGui::Spacing();  // Add spacing between visualizations
    }
    ImGui::End();
}

void ImGuiSDL2OpenGL2Manager::render()
{
    elapsed = SDL_GetTicks() - start;

    if (elapsed < estimated) {
        SDL_Delay(estimated - elapsed);
    }

    ImGui::Render();
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}
