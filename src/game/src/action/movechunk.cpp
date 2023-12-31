#include <game.hpp> 
#include <vector.hpp>

moveChunksAction::moveChunksAction(Game* game, fPoint delta)
{
    this->game = game;
    this->delta = delta;
}

moveChunksAction::moveChunksAction(Game* game, fPoint d, float v)
{
    this->game = game;
    this->direction = d;
    this->speed = v;

    float angle = VECTOR2D::getAngle(direction);
    delta[0] = cos(angle) * speed;
    delta[1] = sin(angle) * speed;
}

moveChunksAction::~moveChunksAction()
{
}

void moveChunksAction::execute()
{
    for(auto& chunk : game->chunks)
    {
        chunk->moveBy(delta);
    }
    game->loadMap();
}

Action* moveChunksAction::clone()
{
    return new moveChunksAction(game, delta);
}
