#include <window.hpp>

Window::~Window()
{
    delete inputBox;
    delete highscore;
    CloseWindow();
}
