#include <window.hpp>

Window::UI::UI()
{
    root_frame = nullptr;
    interface = nullptr;
    obj = nullptr;
}

Window::UI::~UI()
{
    if(root_frame != nullptr) delete root_frame;
    if(interface != nullptr) delete interface;
    if(obj != nullptr) delete obj;
}

void Window::UI::draw()
{
    interface->draw();
    obj->draw();
}

Action* Window::UI::react()
{
    Action* act = interface->react();
    if(act != nullptr) return act;
    return obj->react();
}
