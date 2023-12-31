#include <interface.hpp>

void Interface::drawNested()
{
    for(auto& child : nested)
    {
        child->draw();
    }
}

void Interface::drawContainers()
{
    for(auto& child : containers)
    {
        child->draw();
    }
}

void Interface::draw()
{
    if(!isVisible()) return ;
    Container::draw();

    drawNested();

    drawContainers();


}
