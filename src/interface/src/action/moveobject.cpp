#include <interface.hpp>

moveObjectAction::moveObjectAction(Container* obj, fPoint delta) : obj(obj), delta(delta)
{
}

moveObjectAction::~moveObjectAction()
{
}

void moveObjectAction::execute()
{
    if(!obj->isVisible())
        return;
    obj->moveBy(delta);
}


Action* moveObjectAction::clone()
{
    return new moveObjectAction(obj, delta);
}
