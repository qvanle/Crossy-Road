#include <interface.hpp>

void Interface::drawNested()
{
    for(auto& child : nested)
    {
        if(!child->isVisible()) continue;
        child->draw();
    }
}

void Interface::drawContainers()
{
    for(auto& child : containers)
    {
        if(!child->isVisible()) continue;
        child->draw();
    }
}

void Interface::draw()
{
    if(!isVisible()) return;
    Container::draw();

    drawNested();

    drawContainers();


}
