#include <game.hpp> 

moveChunksAction::moveChunksAction(Game* game, fPoint delta)
{
    this->game = game;
    this->delta = delta;
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
