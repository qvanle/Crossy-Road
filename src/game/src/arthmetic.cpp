#include <game.hpp>

void Game::draw()
{
    if(!isVisible()) return;
    drawNested();

    for(auto i = chunks.begin(); i != chunks.end(); ++i)
    {
        (*i)->draw();
    }

    drawContainers();
}
