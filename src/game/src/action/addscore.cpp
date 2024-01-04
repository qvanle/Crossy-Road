#include <game.hpp>

addScoreAction::addScoreAction(Game* game, Chunk* c)
{
    this->game = game;
    chunk = c;
}

void addScoreAction::execute()
{
    game->score += chunk->getScore();
}

Action* addScoreAction::clone()
{
    return new addScoreAction(game, chunk);
}
