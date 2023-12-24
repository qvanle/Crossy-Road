#include "action.hpp"
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

PacketAction* Container::react()
{
    return nullptr;
}

PacketAction* Container::getRuntimeEvent()
{
    return nullptr;
}
