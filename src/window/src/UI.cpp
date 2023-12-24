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

void Window::UI::setRootFrame(Frame* frame)
{
    if(root_frame != nullptr) 
        delete root_frame;
    root_frame = frame;
}

Frame* Window::UI::getRootFrame() const
{
    return root_frame;
}

void Window::UI::resize(float width, float height)
{
    root_frame->resize(width, height);
}

void Window::UI::setInterfacePool(InterfacePool* inter)
{
    if(interface != nullptr)
        delete interface;
    interface = inter;
}

void Window::UI::load(Interface* inf)
{
    interface->load(inf);
}

void Window::UI::unload(Interface* inf)
{
    interface->unload(inf);
}

Interface* Window::UI::getInterface(std::string s) 
{
    return interface->getInterface(s);
}


void Window::UI::push(std::string s) 
{
    interface->push(s);
}

std::string Window::UI::pop() 
{
    return interface->pop();
}

Interface* Window::UI::top() 
{
    return interface->top();
}
