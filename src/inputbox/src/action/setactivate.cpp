#include <inputbox.hpp>

setActivateAction::setActivateAction(InputBox* but, bool b)
{
    this->but = but;
    this->b = b;
}

setActivateAction::setActivateAction(setActivateAction* other)
{
    this->but = other->but;
    this->b = other->b;
}

void setActivateAction::execute()
{
    but->isActivated = b;
    if(b == false)
    {
        but->framesCounter = 0;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    else
    {
        but->framesCounter++;
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
    }
}

Action* setActivateAction::clone()
{
    return new setActivateAction(this);
}

