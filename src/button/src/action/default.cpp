#include <button.hpp>

defaultAction::defaultAction(ButtonImage* button) 
{
    this->button = button;
}

void defaultAction::execute()
{
    button->chooseImage(0, button->tmpPath);
    button->color = WHITE;
    button->pressing = false;
    button->isHover = false;
    button->clicked = false;
}