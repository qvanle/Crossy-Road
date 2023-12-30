#include <game.hpp>

startInitClockAction::startInitClockAction(Game* game)
{
    this->game = game;
}

void startInitClockAction::execute()
{
    if(!game->initState) return;
    game->initState = false;
    game->initStateClock = std::chrono::system_clock::now();
    game->chunks.clear();
    game->loadMap();
}

Action* startInitClockAction::clone()
{
    return new startInitClockAction(game);
}
