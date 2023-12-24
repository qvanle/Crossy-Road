#include <window.hpp>

void Window::InterfacePool::clearStack()
{
    while(!inf.empty())
    {
        inf.pop();
    }
}

Window::InterfacePool::InterfacePool()
{
}

Window::InterfacePool::~InterfacePool()
{
    clear();
}
   
void Window::InterfacePool::load(Interface* i)
{
    storage[i->getName()] = i;
}

void Window::InterfacePool::unload(Interface* i)
{
    if(storage.find(i->getName()) != storage.end())
    {   
        storage.erase(i->getName());
        delete i;
    }
}

void Window::InterfacePool::clear()
{
    for(auto i : storage)
    {
        delete i.second;
    }
    storage.clear();
    clearStack();
}

Interface* Window::InterfacePool::getInterface(std::string name)
{
    if(storage.find(name) != storage.end())
    {
        return storage[name];
    }
    return nullptr;
}

void Window::InterfacePool::push(std::string name)
{
    if(storage.find(name) != storage.end())
    {
        inf.push(storage[name]);
    }
}

std::string Window::InterfacePool::pop()
{
    if(!inf.empty())
    {
        std::string name = inf.top()->getName();
        inf.pop();
        return name;
    }
    return "";
}

Interface* Window::InterfacePool::top()
{
    if(!inf.empty())
    {
        return inf.top();
    }
    return nullptr;
}

void Window::InterfacePool::draw()
{
    if(!inf.empty())
    {
        inf.top()->draw();
    }
}

PacketAction* Window::InterfacePool::react()
{
    if(!inf.empty())
    {
        return inf.top()->react();
    }
    return nullptr;
}

PacketAction* Window::InterfacePool::getRuntimeEvent()
{
    if(!inf.empty())
    {
        return inf.top()->getRuntimeEvent();
    }
    return nullptr;
}
