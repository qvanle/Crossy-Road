#include "action.hpp"
#include <window.hpp>

Window::UI::UI()
{
    root_frame = nullptr;
    interface = nullptr;
}

Window::UI::~UI()
{
    if(root_frame != nullptr) delete root_frame;
    if(interface != nullptr) delete interface;
}

void Window::UI::draw()
{
    interface->draw();
}

PacketAction* Window::UI::react()
{
    PacketAction* act = interface->react();
    if(act != nullptr) return act;

    return act;
}

PacketAction* Window::UI::getRuntimeEvent() 
{
    PacketAction* act = interface->getRuntimeEvent();
    if(act != nullptr) return act;

    return act;
}
