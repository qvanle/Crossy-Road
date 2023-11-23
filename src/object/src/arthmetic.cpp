#include <object.hpp>

void Object::draw()
{
    if(!visible) return;
    sprites[focus[0]][focus[1]]->draw();
}

void Object::nextSprite()
{
    focus[0]++;
    if(focus[0] >= sprites.size()) focus[0] = 0;
}

void Object::prevSprite()
{
    focus[0]--;
    if(focus[0] < 0) focus[0] = sprites.size() - 1;
}

void Object::setSprite(int index)
{
    if(index < 0 || index >= sprites.size()) return;
    focus[0] = index;
}

void Object::nextTexture()
{
    focus[1] += 1;
    if(focus[1] >= sprites[focus[0]].size()) focus[1] = 0;
}

void Object::prevTexture()
{
    focus[1]--;
    if(focus[1] < 0) focus[1] = sprites[focus[0]].size() - 1;
}

void Object::setTexture(int index)
{
    if(index < 0 || index >= sprites[focus[0]].size()) return;
    focus[1] = index;
}

