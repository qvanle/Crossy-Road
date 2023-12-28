#include <game.hpp>

void Game::draw()
{

    drawNested();

    for(auto i = chunks.begin(); i != chunks.end(); ++i)
    {
        (*i)->draw();
    }
    DrawRectangleLinesEx(main->getFrame(), 5, RED);

    drawContainers();
}
