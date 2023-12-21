#include <interface.hpp>

void Interface::draw()
{
    Container::draw();

    for(auto i : chunks)
        i->draw();

    for(auto& child : containers)
    {
        child->draw();
    }
}
