#include <container.hpp>

Container::~Container()
{
    if(sprites.use_count() == 1)
    {
        for(Sprite & sprite : *sprites)
        {    
            for(auto& frame : sprite)
                delete frame;
            sprite.clear();
        }
    }
}
