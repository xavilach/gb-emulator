#pragma once

#include "gui/windowmanager.hh"
#include "core/gameboy.hh"

#include <memory>
#include <vector>

class Application
{
public:
    Application(int argc, char **argv);
    ~Application();

    Application(const Application &) = delete;            // non-copyable
    Application &operator=(const Application &) = delete; // non-copy-assignable

    void run();

private:
    WindowManager m_windowManager;
    std::unique_ptr<Gameboy> m_gameboy;

    static Application *m_instance;
};
