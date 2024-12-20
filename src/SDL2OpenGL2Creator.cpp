#include "SDL2OpenGL2Creator.hpp"

#include <stdexcept>
#include <string>

#include "SDL.h"
#include "SDL_error.h"

static const int INITIAL_WINDOW_WIDTH = 1280;
static const int INITIAL_WINDOW_HEIGHT = 720;
static const int MINIMAL_WINDOW_WIDTH = 700;
static const int MINIMAL_WINDOW_HEIGHT = 400;

SDL2OpenGL2Creator::SDL2OpenGL2Creator() : window_(nullptr), glContext_(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        throw std::runtime_error("SDL initialization failed: " + std::string(SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window_ = SDL_CreateWindow("Sorting Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INITIAL_WINDOW_WIDTH,
                               INITIAL_WINDOW_HEIGHT, window_flags);
    if (window_ == nullptr) {
        auto err = std::string(SDL_GetError());
        SDL_Quit();
        throw std::runtime_error("SDL initialization failed: " + err);
    }
    SDL_SetWindowMinimumSize(window_, MINIMAL_WINDOW_WIDTH, MINIMAL_WINDOW_HEIGHT);

    glContext_ = SDL_GL_CreateContext(window_);
    SDL_GL_MakeCurrent(window_, glContext_);
    SDL_GL_SetSwapInterval(1);  // Enable vsync
}

SDL2OpenGL2Creator::~SDL2OpenGL2Creator()
{
    if (glContext_) {
        SDL_GL_DeleteContext(glContext_);
        glContext_ = nullptr;
    }

    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    SDL_Quit();
}
