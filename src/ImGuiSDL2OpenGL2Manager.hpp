#ifndef IGGUISDL2OPENGL2MANAGER_HPP
#define IGGUISDL2OPENGL2MANAGER_HPP

#include <SDL_stdinc.h>  // for Uint32
#include <SDL_video.h>

#include <utility>
#include <vector>

#include "IGuiManager.hpp"

struct SettingsData;

class ImGuiSDL2OpenGL2Manager : public IGuiManager {
private:
    SDL_Window* window_;
    SDL_GLContext glContext_;

    Uint32 start_, elapsed_;
    Uint32 estimated_ = 1000 / 20;  // estimated 50 fps

public:
    ImGuiSDL2OpenGL2Manager(SDL_Window* window, SDL_GLContext glContext);
    ImGuiSDL2OpenGL2Manager() = delete;
    ~ImGuiSDL2OpenGL2Manager();
    ImGuiSDL2OpenGL2Manager(const ImGuiSDL2OpenGL2Manager&) = delete;
    ImGuiSDL2OpenGL2Manager(ImGuiSDL2OpenGL2Manager&&) = delete;
    ImGuiSDL2OpenGL2Manager& operator=(const ImGuiSDL2OpenGL2Manager&) = delete;
    ImGuiSDL2OpenGL2Manager& operator=(ImGuiSDL2OpenGL2Manager&&) = delete;

    void startRender() override;
    bool handleExit() override;
    void updateSettings(SettingsData& settingsData) override;
    void updateVisualizationArea(std::vector<std::pair<const char*, const std::vector<int>*> > sortedData) override;
    void render() override;
};

#endif  // IGGUISDL2OPENGL2MANAGER_HPP