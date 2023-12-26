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


Action* moveObjectAction::clone()
{
    return new moveObjectAction(obj, delta);
}
