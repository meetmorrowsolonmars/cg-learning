#include <iostream>

#include <SDL3/SDL.h>
#include <glad/glad.h>

int main(int, char **)
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const auto WINDOW_FLAGS = SDL_WINDOW_OPENGL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (SDL_GL_LoadLibrary(nullptr) < 0)
    {
        std::cerr << "SDL could not load OpenGL. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // TODO: check error
    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window *window = SDL_CreateWindow("CG Learning", SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAGS);

    if (window == nullptr)
    {
        std::cerr << "SDL could not create window. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto context = SDL_GL_CreateContext(window);

    if (context == nullptr)
    {
        std::cerr << "SDL could not create OpenGL context. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0)
    {
        std::cerr << "GLAD could not load OpenGL functions." << std::endl;
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;

    SDL_GL_SetSwapInterval(1);

    int width = 0;
    int height = 0;

    SDL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(1.0f, 0.2f, 0.6f, 1.0f);

    std::cout << "Window size: " << width << " " << height << std::endl;
    std::cout << "Hello, from cg-learning!" << std::endl;

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.keysym.sym == SDLK_q)
            {
                quit = true;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
