#include <interface.hpp>
#include <vector.hpp>

moveObjectAction::moveObjectAction(Container* obj, fPoint delta) : obj(obj), delta(delta)
{
}

moveObjectAction::moveObjectAction(Container* obj, fPoint dir, float speed) : obj(obj), dir(dir), speed(speed)
{
    float angle = VECTOR2D::getAngle(dir);
    delta[0] = cos(angle) * speed;
    delta[1] = sin(angle) * speed;
}

moveObjectAction::~moveObjectAction()
{
}

void moveObjectAction::execute()
{
    obj->moveBy(delta);
}


Action* moveObjectAction::clone()
{
    return new moveObjectAction(obj, delta);
}

movetoObjectAction::movetoObjectAction(Container* obj, fPoint pos) : obj(obj), pos(pos)
{
}

movetoObjectAction::~movetoObjectAction()
{
}

void movetoObjectAction::execute()
{
    obj->moveTo(pos);
}

Action* movetoObjectAction::clone()
{
    return new movetoObjectAction(obj, pos);
}
