#include <action.hpp>

Action::Action()
{
    repeat = 1;
}

Action::Action(int repeat)
{
    this->repeat = repeat;
}

Action::Action(Action* action)
{
    repeat = action->repeat;
}

void Action::setRepeat(int repeat)
{
    this->repeat = repeat;
}

void Action::doneExecute()
{
    if(repeat > 0)
        repeat--;
}

void Action::ForceEnd()
{
    repeat = 0;
}

void Action::Interrupt()
{
    repeat = 0;
}

Action* Action::clone()
{
    return this;
}

int Action::getRepeat() const
{
    if(repeat == -1) return 2;
    return repeat;
}

bool Action::isInfinite() const
{
    return repeat == -1;
}

bool Action::isFinished() const
{
    return repeat == 0;
}
