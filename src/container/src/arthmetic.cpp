#include <container.hpp>

void Container::draw()
{
    if(sprites.empty()) return;
    if(!visible) return;
    sprites[focus[0]][focus[1]]->draw();
}

void Container::show()
{
    visible = true;
}

void Container::hide()
{
    visible = false;
}

void Container::toggleVisibility()
{
    visible = !visible;
}

bool Container::isVisible()
{
    return visible;
}

int Container::getInstanceId()
{
    return instance_id;
}

int Container::sizeSprite()
{
    return sprites.size();
}

int Container::SpriteSize(int index)
{
    return (sprites)[index].size();
}

void Container::nextSprite()
{
    focus[0] = (focus[0] + 1) % sprites.size();
}

void Container::nextImageInSprite()
{
    focus[1] = (focus[1] + 1) % (sprites)[focus[0]].size();
}

void Container::nextImage()
{
    if (focus[1] + 1 < (sprites)[focus[0]].size())
        focus[1]++;
    else
    {
        focus[1] = 0;
        nextSprite();
    }
}
Action* Container::react()
{
    return nullptr;
}

Action* Container::runtimeEvent()
{
    return nullptr;
}
