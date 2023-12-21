#include <game.hpp>

void Game::draw()
{

    drawNested();

    for(auto& child : chunks)
    {
        child->draw();
    }

    drawContainers();
}
