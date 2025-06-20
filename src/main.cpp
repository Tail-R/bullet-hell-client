#define SDL_MAIN_HANDLED

#include <iostream>
#include <fstream>

#ifdef _WIN32
    #include <windows.h>
#endif

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh/mesh.hpp"
#include "texture/texture2d.hpp"
#include "shader/shader.hpp"

constexpr int SCREEN_WIDTH  = 600;
constexpr int SCREEN_HEIGHT = 800;

constexpr int FPS = 60;
constexpr int FRAME_DELAY = 1000 / FPS;

constexpr std::string_view IMAGE_PATH           = "../images/zmon_2001.png";
constexpr std::string_view VERTEX_SHADER_PATH   = "../glsl/vertex/vertex.glsl";
constexpr std::string_view FRAGMENT_SHADER_PATH = "../glsl/fragment/fragment.glsl";

// SDL
bool g_sdl2_initialized = false;
SDL_Window* g_window = NULL;
SDL_GLContext g_gl_context = NULL;

// OpenGL
bool g_gl_initialized = false;

bool init_renderer() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
    }
    else
    {
        g_sdl2_initialized = true;

        g_window = SDL_CreateWindow(
            "Hello Modern OpenGL",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL
        );

        if (g_window == NULL)
        {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        }
        else
        {
            g_gl_context = SDL_GL_CreateContext(g_window);

            if (!g_gl_context)
            {
                std::cerr << "OpenGL context could not be created!" << '\n';
            }
            else
            {
                return true;
            }
        }
    }

    return false;
}

void clean_up_renderer() {
    if (g_window != NULL)
    {
        SDL_DestroyWindow(g_window);
        g_window = NULL;
    }

    if (g_sdl2_initialized)
    {
        SDL_Quit();
        g_sdl2_initialized = false;
    }
}

bool init_gl() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << '\n';

        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.f);

    g_gl_initialized = true;

    return true;
}

void draw_loop() {
    if (!g_sdl2_initialized || !g_gl_initialized)
    {
        return;
    }

    // Create shader
    Shader shader(
        VERTEX_SHADER_PATH,
        FRAGMENT_SHADER_PATH
    );

    // Create texture
    Texture2DConfig tex_conf = {};
    Texture2D texture;
    bool tex_load_succeed = texture.load_from_file(IMAGE_PATH, tex_conf);

    int w = texture.width();
    int h = texture.height();

    float scale_x = 1.0f;
    float scale_y = 1.0f;
    float scale_factor = 0.4f;
    float texture_aspect = 0.0f;

    if (tex_load_succeed)
    {
        float screen_aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
        texture_aspect = (float)w / (float)h;

        if (screen_aspect > texture_aspect)
        {
            scale_x = texture_aspect / screen_aspect;
        }
        else
        {
            scale_y = screen_aspect / texture_aspect;
        }
    }
    else
    {
        std::cerr << "Failed to load texture" << '\n';

        return;
    }

    std::vector<GLfloat> quad_vertices {
        // Positions        // Texcoords
        -scale_x * scale_factor,  scale_y * scale_factor, 0.0f,  0.0f, 1.0f,
        -scale_x * scale_factor, -scale_y * scale_factor, 0.0f,  0.0f, 0.0f,
         scale_x * scale_factor, -scale_y * scale_factor, 0.0f,  1.0f, 0.0f,
         scale_x * scale_factor,  scale_y * scale_factor, 0.0f,  1.0f, 1.0f
    };

    std::vector<GLuint> quad_indices {
        0, 1, 2,
        2, 3, 0
    };

    Mesh quad_mesh(quad_vertices, quad_indices, {3, 2});

    shader.use();
    shader.set_int("OurTexture", 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.f);

    SDL_GL_SetSwapInterval(1);
    SDL_ShowWindow(g_window);

    SDL_Event e;
    float x_offset = 0.0f;
    float y_offset = 0.0f;
    float speed = 2.0f;
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    float totalTime = 0.0f;
    bool quit = false;

    while (!quit)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        float delta_time = (now - last) / (float)SDL_GetPerformanceFrequency();

        totalTime += delta_time;

        glClear(GL_COLOR_BUFFER_BIT);

        while (SDL_PollEvent(&e) != 0) 
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        
        auto keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_RIGHT])   x_offset += speed * delta_time;
        if (keystate[SDL_SCANCODE_LEFT])    x_offset -= speed * delta_time;
        if (keystate[SDL_SCANCODE_UP])      y_offset += speed * delta_time;
        if (keystate[SDL_SCANCODE_DOWN])    y_offset -= speed * delta_time;

        shader.use();
        shader.set_float("time", totalTime);
        shader.set_vec2("offset", glm::vec2(x_offset, y_offset));

        texture.bind();

        quad_mesh.bind();
        quad_mesh.draw();

        SDL_GL_SwapWindow(g_window);
    }
}

int main(int argc, char* args[]) {
    if (!init_renderer() || !init_gl())
    {
        clean_up_renderer();

        return 1;
    }
    
    draw_loop();

    clean_up_renderer();

    return 0;
}