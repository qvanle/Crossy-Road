#include <chunk.hpp>

Chunk::~Chunk()
{
    for(auto i : visiter)
        delete i;

    while(!Entity.empty())
    {
        delete Entity.back();
        Entity.pop_back();
    }
    if(trafficLight != nullptr)
        delete trafficLight;
}

