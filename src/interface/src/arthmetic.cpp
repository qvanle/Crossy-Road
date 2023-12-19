#include <interface.hpp>

void Interface::draw()
{
    Container::draw();

    for(auto& child : nested)
    {
        child->draw();
    }

    for(auto& child : containers)
    {
        child->draw();
    }
}
