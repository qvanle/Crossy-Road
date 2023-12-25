#include <chunk.hpp>

void Chunk::drawEntity() 
{
    for(auto i : Entity)
    {
        if(!i->isVisible()) continue;
        i->draw();
    }
}

void Chunk::draw() 
{

    if(!isVisible()) return ;
    Container::draw();
    drawNested();
    drawContainers();
    drawEntity();
}
