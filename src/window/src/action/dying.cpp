#include <game.hpp>

dyingAction::dyingAction(Game* game) : game(game) {}

void dyingAction::execute()
{
    if(game->dieIndex == 6) 
    {
        game->isDying = false;
        game->dieIndex = 0;
        return ;
    }
    game->isLose = true;
    game->main->chooseImage(4, game->dieIndex++);
}

Action* dyingAction::clone()
{
    return new dyingAction(*this);
}
