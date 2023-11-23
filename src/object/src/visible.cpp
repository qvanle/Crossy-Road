#include <object.hpp>

void Object::hide()
{
    visible = false;
}

void Object::show()
{
    visible = true;
}

void Object::toggleVisibility()
{
    visible = !visible;
}

bool Object::isVisible()
{
    return visible;
}
