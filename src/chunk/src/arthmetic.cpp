#include <chunk.hpp>

void Chunk::drawEntity() 
{
    for(auto i : Entity)
        i->draw();
}

void Chunk::draw() 
{

    Container::draw();
    drawNested();
    drawContainers();
    drawEntity();
}
