#include <game.hpp>

startInitClockAction::startInitClockAction(Game* game)
{
    this->game = game;
}

void startInitClockAction::execute()
{
    if(!game->initState) return;
    game->score = 0;
    game->initState = false;
    game->initStateClock = std::chrono::system_clock::now();
    game->chunks.clear();
    game->loadMap();
    game->main->moveTo({0.5, 0.5});
}

Action* startInitClockAction::clone()
{
    return new startInitClockAction(game);
}
