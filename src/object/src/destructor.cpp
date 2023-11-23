#include <object.hpp>

void Object::clearSprites()
{
    for(auto& spr : sprites)
    {
        for(int i = 0; i < spr.size(); i++)
        {
            delete spr[i];
        }
        spr.clear();
    }
}

Object::~Object() 
{
    clearSprites();
}
