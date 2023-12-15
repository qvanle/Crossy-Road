#include <button.hpp>
hoverAction::hoverAction(ButtonImage* button) 
{
    this->button = button;
}

void hoverAction::execute()
{
    button->chooseImage(1, button->tmpPath);
}
