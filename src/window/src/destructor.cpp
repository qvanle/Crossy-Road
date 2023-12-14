#include <window.hpp>

Window::~Window()
{

    for (auto& thread : Wcontent.thread_pool)
        thread.join();

    CloseWindow();
}
