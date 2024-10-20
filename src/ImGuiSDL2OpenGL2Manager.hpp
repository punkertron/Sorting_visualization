#ifndef IGGUISDL2OPENGL2MANAGER_HPP
#define IGGUISDL2OPENGL2MANAGER_HPP

#include "IGuiManager.hpp"

#include <SDL.h>
#include <SDL_opengl.h>
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
    void updateData(SettingsData& settingsData) override;
    void render() override;
};

#endif // IGGUISDL2OPENGL2MANAGER_HPP