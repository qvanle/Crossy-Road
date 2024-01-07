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
    Rectangle rect = main->getFrame();
    // draw hitbox of 5px 
    // DrawRectangleLinesEx(rect, 5, RED);
    // drawContainers();

    // draw rectangle color white on top right 
    
    Rectangle rel = getFrame();
    rel.x = rel.width * 0.0;
    rel.y = 0;
    rel.width *= 0.15;
    rel.height *= 0.06;

    DrawRectangleRec(rel, {200, 200, 200, 255});
    DrawText(TextFormat("Score: %08i", score), rel.x + 10, 25, 20, RED);
}
