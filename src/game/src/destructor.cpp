#include <game.hpp>


Game::~Game()
{
    for(auto &i : cache)
    {
        delete i;
    }

    for(auto &i : chunks)
    {
        delete i;
    }
}
