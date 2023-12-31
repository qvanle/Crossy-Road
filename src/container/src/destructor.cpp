#include <container.hpp>

Container::~Container()
{
    for(Sprite & sprite : sprites)
    {    
        for(auto& frame : sprite)
            delete frame;
        sprite.clear();
    }
}
