#include <window.hpp>

Window::~Window()
{

    UI.~UI();
    immediate_pool.~ActionPool();
    duration_pool.~ActionPool();

    for (auto& thread : Wcontent.thread_pool)
        thread.join();

    CloseWindow();
}
