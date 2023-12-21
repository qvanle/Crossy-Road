#include <game.hpp>

void Game::draw()
{

    drawNested();

    for(auto i = chunks.rbegin(); i != chunks.rend(); ++i)
    {
        (*i)->draw();
    }

    drawContainers();
}
