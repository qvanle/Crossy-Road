#include <interface.hpp>

movetoObjectAction::movetoObjectAction(Container* obj, fPoint pos) 
{
    this->obj = obj;
    this->pos = pos;
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
