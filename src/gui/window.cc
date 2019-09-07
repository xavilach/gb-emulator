#include "gui/window.hh"

#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>

Window::Window(const std::string &title, int height, int width)
    : m_height(height), m_width(width),
      m_window(nullptr), m_renderer(nullptr), m_windowID(0),
      m_mouseFocus(true), m_keyboardFocus(true),
      m_fullScreen(false), m_minimized(false), m_shown(true)
{
    m_window = SDL_CreateWindow(title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_height,
                                m_width,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!m_window)
    {
        throw std::runtime_error("SDL_CreateWindow failed.");
    }

    m_windowID = SDL_GetWindowID(m_window);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_renderer)
    {
        throw std::runtime_error("SDL_CreateRenderer failed.");
    }

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
}

Window::~Window()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Window::handleEvent(SDL_Event &e)
{
    /* Filter out event not targeted to this window. */
    if (SDL_WINDOWEVENT != e.type)
        return;
    if (m_windowID != e.window.windowID)
        return;

    switch (e.window.event)
    {
        /* Window shown */
    case SDL_WINDOWEVENT_SHOWN:
        m_shown = true;
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        m_shown = false;
        break;

    case SDL_WINDOWEVENT_EXPOSED:
        SDL_RenderPresent(m_renderer);
        break;

        /* Window size. */
    case SDL_WINDOWEVENT_RESIZED:
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        m_width = e.window.data1;
        m_height = e.window.data2;
        SDL_RenderPresent(m_renderer);
        break;

        /* Minimized. */
    case SDL_WINDOWEVENT_MINIMIZED:
        m_minimized = true;
        break;
    case SDL_WINDOWEVENT_MAXIMIZED:
    case SDL_WINDOWEVENT_RESTORED:
        m_minimized = false;
        break;

        /* Mouse focus. */
    case SDL_WINDOWEVENT_ENTER:
        m_mouseFocus = true;
        break;
    case SDL_WINDOWEVENT_LEAVE:
        m_mouseFocus = false;
        break;

        /* Keyboard focus. */
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        m_keyboardFocus = true;
        break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
        m_keyboardFocus = false;
        break;

    case SDL_WINDOWEVENT_CLOSE:
        SDL_HideWindow(m_window);
        break;

    case SDL_WINDOWEVENT_TAKE_FOCUS:
    case SDL_WINDOWEVENT_HIT_TEST:
    case SDL_WINDOWEVENT_MOVED:
    default:
        /* Ignore. */
        break;
    }
}

void Window::focus()
{
    if (!m_shown)
    {
        SDL_ShowWindow(m_window);
    }

    SDL_RaiseWindow(m_window);
}

void Window::render()
{
    if (!m_minimized)
    {
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderClear(m_renderer);

        SDL_RenderPresent(m_renderer);
    }
}

int Window::getWidth() const
{
    return m_width;
}

int Window::getHeight() const
{
    return m_height;
}

bool Window::hasMouseFocus() const
{
    return m_mouseFocus;
}

bool Window::hasKeyboardFocus() const
{
    return m_keyboardFocus;
}

bool Window::isMinimized() const
{
    return m_minimized;
}

bool Window::isShown() const
{
    return m_shown;
}
