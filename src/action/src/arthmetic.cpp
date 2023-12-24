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

bool Action::isPackage()
{
    return false;
}

Action* Action::clone()
{
    return this;
}

std::vector<Action*> Action::unpack()
{
    return std::vector<Action*> ();
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

bool PacketAction::isPackage() 
{
    return true;
}

void PacketAction::addAction(Action* action)
{
    actions.push_back(action);
}

void PacketAction::addAction(PacketAction* action) 
{
    for(auto i : action->actions)
        actions.push_back(i);
    action->actions.clear();
}

std::vector<Action*> PacketAction::unpack()
{
    std::vector<Action*> unpacked;

    for(Action* a : actions) 
        unpacked.push_back(a);

    actions.clear();

    return unpacked;
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
