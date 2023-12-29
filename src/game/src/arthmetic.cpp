#include <game.hpp>

void Game::draw()
{

    drawNested();

    for(auto i = chunks.begin(); i != chunks.end(); ++i)
    {
        if(*i != nullptr) 
        {
            (*i)->draw();
        }else std::cout << i - chunks.begin() << " is nullptr" << std::endl;
    }
    DrawRectangleLinesEx(main->getFrame(), 5, RED);

    drawContainers();
}
