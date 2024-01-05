#include <chunk.hpp>

switchTrafficLightAction::switchTrafficLightAction(Chunk* chunk)
{
    this->chunk = chunk;
}

switchTrafficLightAction::~switchTrafficLightAction()
{
}

void switchTrafficLightAction::execute()
{
    if(chunk->trafficLight == nullptr) return ;
    chunk->stop = !chunk->stop;
    chunk->trafficLight->chooseSprite(chunk->stop);
}

Action* switchTrafficLightAction::clone()
{
    return new switchTrafficLightAction(chunk);
}
