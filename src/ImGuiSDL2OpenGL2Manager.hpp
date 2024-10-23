#ifndef IGGUISDL2OPENGL2MANAGER_HPP
#define IGGUISDL2OPENGL2MANAGER_HPP

#include <SDL.h>
#include <SDL_opengl.h>

#include "IGuiManager.hpp"
#include "imgui.h"

class ImGuiSDL2OpenGL2Manager : public IGuiManager {
private:
    SDL_Window* window;
    SDL_GLContext glContext;

public:
    ImGuiSDL2OpenGL2Manager(SDL_Window* window, SDL_GLContext glContext);
    ImGuiSDL2OpenGL2Manager() = delete;
    ~ImGuiSDL2OpenGL2Manager();
    ImGuiSDL2OpenGL2Manager(const ImGuiSDL2OpenGL2Manager&) = delete;
    ImGuiSDL2OpenGL2Manager(ImGuiSDL2OpenGL2Manager&&) = delete;
    ImGuiSDL2OpenGL2Manager& operator=(const ImGuiSDL2OpenGL2Manager&) = delete;
    ImGuiSDL2OpenGL2Manager& operator=(ImGuiSDL2OpenGL2Manager&&) = delete;

    bool handleExit() override;
    void updateSettings(SettingsData& settingsData) override;
    void updateVisualizationArea(std::unordered_map<const char*, const std::vector<int>*> sortedData);
    void render() override;
};

#endif  // IGGUISDL2OPENGL2MANAGER_HPP