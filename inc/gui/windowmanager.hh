#pragma once

#include "gui/window.hh"

#include <memory>
#include <vector>

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();

    void create();
    void create(const std::string &title, int height, int width);

    void handleEvent(SDL_Event &e);
    void render();

    int opened();

private:
    std::vector<std::unique_ptr<Window>> m_windows;
};
