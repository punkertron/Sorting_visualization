#include <iostream>
#include <memory>
#include <stdexcept>

#include "Controller.hpp"
#include "ImGuiSDL2OpenGL2Manager.hpp"
#include "SDL2OpenGL2Creator.hpp"
#include "SortingManager.hpp"

int main()
{
    try {
        auto sdlCreator = std::make_unique<SDL2OpenGL2Creator>();
        auto guiManager = std::make_unique<ImGuiSDL2OpenGL2Manager>(sdlCreator->getWindow(), sdlCreator->getContext());
        auto sortingManager = std::make_unique<SortingManager>();
        Controller c(std::move(guiManager), std::move(sortingManager));
        c.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
