#include <inputbox.hpp>

setRawTextAction::setRawTextAction(InputBox* inputBox, std::string rawText)
{
    this->but = inputBox;
    this->s = rawText;
}

setRawTextAction::setRawTextAction(setRawTextAction* other)
{
    this->but = other->but;
    this->s = other->s;
}

void setRawTextAction::execute()
{
    this->but->rawText = this->s;
}

Action* setRawTextAction::clone()
{
    return new setRawTextAction(this);
}


