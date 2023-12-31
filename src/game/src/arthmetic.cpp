#include <game.hpp>

void Game::draw()
{
    if(!isVisible()) return;
    drawNested();

    for(auto i = chunks.begin(); i != chunks.end(); ++i)
    {
        if(*i != nullptr) 
        {
            (*i)->draw();
        }else std::cout << i - chunks.begin() << " is nullptr" << std::endl;
    }
    main->draw();
    drawContainers();
}
