#include <window.hpp>

Window::~Window()
{

    delete interface;

    delete root_frame;
    for (auto& thread : thread_pool)
        thread.join();

    CloseWindow();
}
