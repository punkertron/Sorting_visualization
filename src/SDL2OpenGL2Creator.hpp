#ifndef SDL2OPENGL2CREATOR_HPP
#define SDL2OPENGL2CREATOR_HPP

#include <SDL.h>
#include <SDL_opengl.h>

class SDL2OpenGL2Creator {
private:
    SDL_Window* window;
    SDL_GLContext glContext;

public:
    SDL2OpenGL2Creator();
    ~SDL2OpenGL2Creator();
    SDL2OpenGL2Creator(const SDL2OpenGL2Creator&) = delete;
    SDL2OpenGL2Creator(SDL2OpenGL2Creator&&) = delete;
    SDL2OpenGL2Creator& operator=(const SDL2OpenGL2Creator&) = delete;
    SDL2OpenGL2Creator& operator=(SDL2OpenGL2Creator&&) = delete;

    SDL_Window* getWindow()
    {
        return window;
    }
    SDL_GLContext getContext()
    {
        return glContext;
    }
};

#endif  // SDL2OPENGL2CREATOR_HPP