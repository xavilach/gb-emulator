#pragma once

#include <SDL2/SDL.h>
#include <string>

class Window
{
public:
    Window(const std::string &title = "", int height = 640, int width = 480);
    ~Window();

    Window(const Window &) = delete;            // non-copyable
    Window &operator=(const Window &) = delete; // non-copy-assignable

    void handleEvent(SDL_Event &e);
    void focus();
    void render();

    int getWidth() const;
    int getHeight() const;

    bool hasMouseFocus() const;
    bool hasKeyboardFocus() const;
    bool isMinimized() const;
    bool isShown() const;

private:
    /* Window dimension */
    int m_height;
    int m_width;

    /* Window data */
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Uint32 m_windowID;

    /* Window focus */
    bool m_mouseFocus;
    bool m_keyboardFocus;
    bool m_fullScreen;
    bool m_minimized;
    bool m_shown;
};
