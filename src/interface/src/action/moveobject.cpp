#include <interface.hpp>

moveObjectAction::moveObjectAction(Container* obj, fPoint delta) : obj(obj), delta(delta)
{
}

moveObjectAction::~moveObjectAction()
{
}

void moveObjectAction::execute()
{
    obj->moveBy(delta);
}

void moveObjectAction::Interrupt()
{
}

void moveObjectAction::ForceEnd()
{
}

Action* moveObjectAction::clone()
{
    return new moveObjectAction(obj, delta);
}
