#include <interface.hpp>

void Interface::draw()
{
    Container::draw();

    for(auto& child : containers)
    {
        child->draw();
    }
}

void Interface::push(Container* contain)
{
	containers.push_back(contain);
}

void Interface::pop()
{
	containers.pop_back();
}

Container* Interface::get()
{
	return nullptr;
}

Action* Interface::getRuntimeEvent()
{
	return nullptr;
}
