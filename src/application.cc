#include "application.hh"

#include "gui/window.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <memory>
#include <iostream>
#include <stdexcept>

Application *Application::m_instance = nullptr;

Application::Application(int argc, char **argv)
    : m_windowManager(), m_gameboy(nullptr)
{
    if (m_instance)
    {
        throw std::runtime_error("Application already created.");
    }

    if (argc < 2)
    {
        throw std::runtime_error("Usage: gb-emulator [path/to/rom.bin]");
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw std::runtime_error("SDL_Init failed.");
    }

    if (TTF_Init() != 0)
    {
        throw std::runtime_error("TTF_Init failed.");
    }

    m_instance = this;

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    m_windowManager.create(argv[1], 600, 400);

    m_gameboy = std::make_unique<Gameboy>(argv[1]);
}

Application::~Application()
{
    TTF_Quit();

    SDL_Quit();
}

void Application::run()
{
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        const Uint32 minimumFrameTime = 1000 / 60;
        Uint32 loopStart = SDL_GetTicks();

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }

            m_windowManager.handleEvent(e);
        }

        m_windowManager.render();

        if (0 == m_windowManager.opened())
        {
            quit = true;
        }

        Uint32 delta = SDL_GetTicks() - loopStart;

        if (delta < minimumFrameTime)
            SDL_Delay(minimumFrameTime - delta);
    }
}
