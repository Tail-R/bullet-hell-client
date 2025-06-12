#pragma once

#include <cstddef>
#include <string_view>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Renderer {
public:
    Renderer(std::string_view window_title, size_t window_width, size_t window_height);
    ~Renderer();

private:
    void initialize();
    bool m_renderer_ready;
};