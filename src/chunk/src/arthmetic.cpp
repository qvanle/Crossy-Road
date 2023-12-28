#include <chunk.hpp>

void Chunk::drawEntity() 
{
    for(auto i : Entity)
    {
        i->draw();

        DrawRectangleLinesEx(i->getFrame(), 5, RED);
    }
}

void Chunk::draw() 
{

    Container::draw();
    drawNested();
    drawContainers();
    drawEntity();
}
