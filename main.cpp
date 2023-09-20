#include <iostream>
#include <thread>

#include <SDL3/SDL.h>

using namespace std::chrono_literals;

int main(int, char **)
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const auto WINDOW_FLAGS = SDL_EVENT_WINDOW_SHOWN;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("CG Learning", SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAGS);

    if (window == nullptr)
    {
        std::cerr << "SDL could not create window. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr)
    {
        std::cerr << "SDL could not create renderer. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto surface = SDL_GetWindowSurface(window);
    if (surface == nullptr)
    {
        std::cerr << "SDL window have not surface. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (SDL_FillSurfaceRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF)) < 0)
    {
        std::cerr << "SDL could not fill surface. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (SDL_UpdateWindowSurface(window) < 0)
    {
        std::cerr << "SDL could not update window surface. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "Hello, from cg-learning!\n";

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
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
