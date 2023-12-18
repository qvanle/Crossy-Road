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

bool Action::isRequest()
{
    return false;
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

PacketAction::PacketAction() : Action()
{
}

PacketAction::PacketAction(int repeat) : Action(repeat)
{
}

PacketAction::PacketAction(PacketAction* action) : Action(action)
{
    for(Action* a : action->actions)
        actions.push_back(a->clone());
}

PacketAction::~PacketAction()
{
    for(Action* a : actions)
        delete a;
    actions.clear();
}

void PacketAction::addAction(Action* action)
{
    actions.push_back(action);
}

void PacketAction::execute()
{
    for(Action* a : actions)
    {
        if(a->isFinished()) continue;
        a->execute();
    }
    doneExecute();
}


void PacketAction::ForceEnd()
{
    Action::ForceEnd();
}

void PacketAction::Interrupt()
{
    Action::Interrupt();
}

PacketAction* PacketAction::clone()
{
    return new PacketAction(this);
}
