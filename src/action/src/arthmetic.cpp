#include <action.hpp>

void Action::ForceEnd()
{
    repeat = 0;
}

void Action::Interrupt()
{
    repeat = 0;
}

int Action::getRepeat() const
{
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
