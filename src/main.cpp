#include "SDL2OpenGL2Creator.hpp"
#include "ImGuiSDL2OpenGL2Manager.hpp"
#include "Controller.hpp"

#include <memory>
#include <stdexcept>
#include <iostream>

int main()
{
    try {
        auto sdlCreator = std::make_unique<SDL2OpenGL2Creator>();
        auto guiManager = std::make_unique<ImGuiSDL2OpenGL2Manager>(sdlCreator->getWindow(), sdlCreator->getContext());
        Controller c(std::move(guiManager));
        c.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
