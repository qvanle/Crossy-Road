#include <action.hpp>

Action::Action()
{
}

Action::Action(Action* action)
{
}


bool Action::isRequest()
{
    return false;
}

Action* Action::clone()
{
    return this;
}


PacketAction::PacketAction() : Action()
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
        a->execute();
    }
}


PacketAction* PacketAction::clone()
{
    return new PacketAction(this);
}
