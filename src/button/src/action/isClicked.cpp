#include <button.hpp>

isClickedAction::isClickedAction(ButtonImage* button) 
{
    this->button = button;
}

void isClickedAction::execute()
{
    button->nextImageInSprite();
}