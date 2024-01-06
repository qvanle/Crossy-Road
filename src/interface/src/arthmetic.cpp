#include <interface.hpp>

void Interface::drawNested()
{
    for (auto &child : nested)
    {
        child->draw();
    }
}

void Interface::drawContainers()
{
    for (auto &child : containers)
    {
        child->draw();
    }
}

void Interface::draw()
{
    if (!isVisible())
        return;
    Container::draw();

    drawNested();

    drawContainers();

//     if (getName() == "gameover")
//     {
//         Rectangle rel = getFrame();
//         rel.x = rel.width * 1.0 ;
//         rel.y = rel.height * 0.8;
//         rel.width *= 0.3;
//         rel.height *= 0.12;

//         DrawText(TextFormat("%08i", score), rel.x , rel.y, 40, RED);
//     }
}

void Interface::setScore(int score)
{
    
}

int Interface::getScore()
{
    return 0;
}