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
    if(!tryReading()) return ;
    interface->draw();
    endReading();
}

Action* Window::UI::react()
{
    if(!tryReading()) return nullptr;
    Action* act = interface->react();
    endReading();

    return act;
}

Action* Window::UI::getRuntimeEvent() 
{
    if(!tryReading()) return nullptr;
    Action* act = interface->getRuntimeEvent();
    endReading();

    return act;
}

void Window::UI::setRootFrame(Frame* frame)
{
    if(root_frame != nullptr) 
        delete root_frame;
    root_frame = frame;
}

Frame* Window::UI::getRootFrame()
{
    return root_frame;
}

void Window::UI::resize(float width, float height)
{
    writing();
    root_frame->resize(width, height);
    endWriting();
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
    reading();
    Interface* f = interface->getInterface(s);
    endReading();
    return f;
}


void Window::UI::push(std::string s) 
{
    writing();
    interface->push(s);
    endWriting();
}

std::string Window::UI::pop() 
{
    writing();
    std::string f =  interface->pop();
    endWriting();
    return f;
}

Interface* Window::UI::top() 
{
    reading();
    Interface* f = interface->top();
    endReading();
    return f;
}

bool Window::UI::isReadable()
{
    std::lock_guard<std::mutex> lock(mtx);
    return !noRead;
}

bool Window::UI::isWritable()
{
    std::lock_guard<std::mutex> lock(mtx);
    return !noWrite;
}

void Window::UI::reading()
{
    do 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        std::lock_guard<std::mutex> lock(mtx);
        if(noRead) return ;
        reader++;
        return ;
    }while(true);
}

bool Window::UI::tryReading()
{
    std::lock_guard<std::mutex> lock(mtx);
    if(noRead) return false;
    reader++;

    return true;
}

void Window::UI::endReading()
{
    std::lock_guard<std::mutex> lock(mtx);
    reader--;
}

void Window::UI::writing()
{
    do 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        std::lock_guard<std::mutex> lock(mtx);
        if(noWrite) return ;
        writer++;
        noRead = true;
        return;
    }while(true);
}

bool Window::UI::tryWriting()
{
    std::lock_guard<std::mutex> lock(mtx);
    if(noWrite) return false;
    writer++;
    noRead = true;
    return true;
}

void Window::UI::endWriting()
{
    std::lock_guard<std::mutex> lock(mtx);
    writer--;
    if(writer == 0) noRead = false;
}

void Window::UI::DenyRead()
{
    std::lock_guard<std::mutex> lock(mtx);
    noRead = true;
}

void Window::UI::AllowRead()
{
    std::lock_guard<std::mutex> lock(mtx);
    noRead = false;
}

void Window::UI::DenyWrite()
{
    std::lock_guard<std::mutex> lock(mtx);
    noWrite = true;
}

void Window::UI::AllowWrite()
{
    std::lock_guard<std::mutex> lock(mtx);
    noWrite = false;
}


