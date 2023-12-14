#include <window.hpp>

Window::~Window()
{

    UI.~UI();

    for (auto& thread : Wcontent.thread_pool)
        thread.join();

    CloseWindow();
}
