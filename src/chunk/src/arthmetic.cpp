#include <chunk.hpp>

void Chunk::drawEntity() 
{
    for(auto i : Entity)
    {
        // DrawRectangleLinesEx(i->getFrame(), 5, RED);
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
    if(trafficLight != nullptr) 
        trafficLight->draw();
}
