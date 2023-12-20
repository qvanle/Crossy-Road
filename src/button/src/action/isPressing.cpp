#include <button.hpp>

isPressingAction::isPressingAction(ButtonImage* button) 
{
    this->button = button;
}

void isPressingAction::execute()
{
    button->chooseImage(2, button->tmpPath);
}