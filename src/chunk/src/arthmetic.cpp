#include <chunk.hpp>

void Chunk::drawEntity() 
{
    for(auto i : Entity)
    {
        i->draw();
    }
}

void Chunk::draw() 
{
    if(!isVisible()) return;
    Container::draw();
    drawNested();
    drawContainers();
    drawEntity();
}
