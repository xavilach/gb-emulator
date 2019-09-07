#include "gui/windowmanager.hh"

WindowManager::WindowManager()
    : m_windows()
{
}

WindowManager::~WindowManager()
{
}

void WindowManager::create()
{
    m_windows.push_back(std::make_unique<Window>());
}

void WindowManager::create(const std::string &title, int height, int width)
{
    m_windows.push_back(std::make_unique<Window>(title, height, width));
}

void WindowManager::handleEvent(SDL_Event &e)
{
    for (auto const &window : m_windows)
    {
        window->handleEvent(e);
    }
}

void WindowManager::render()
{
    for (auto const &window : m_windows)
    {
        window->render();
    }
}

int WindowManager::opened()
{
    int count = 0;

    for (auto const &window : m_windows)
    {
        if (window->isShown())
        {
            count++;
        }
    }

    return count;
}
