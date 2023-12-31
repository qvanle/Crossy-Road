#include <action.hpp>
#include <queue>

ARGS NONE_ARGS;

Action::Action()
{
}

Action::Action(Action* action)
{
}


int Action::isRequest()
{
    return 0;
}

bool Action::isPackage()
{
    return false;
}

void Action::execute()
{
}

Action* Action::clone()
{
    return this;
}

std::vector<Action*> Action::unpack()
{
    return std::vector<Action*> ({this});
}

ARGS& Action::getArgs()
{
    return NONE_ARGS;
}

PacketAction::PacketAction() : Action()
{
}


PacketAction::PacketAction(PacketAction* other) : Action(other)
{
    for(Action* a : other->actions)
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

void PacketAction::addAction(PacketAction* other) 
{
    for(auto i : other->actions)
        actions.push_back(i);
    other->actions.clear();
    delete other;
}

std::vector<Action*> PacketAction::unpack()
{
    std::vector<Action*> unpacked;
    std::queue<PacketAction*> q;

    q.push(this);

    while(!q.empty()) 
    {
        PacketAction* p = q.front();
        q.pop();

        for(Action* a : p->actions)
        {
            if(a->isPackage())
            {
                q.push((PacketAction*)a);
            }
            else
            {
                unpacked.push_back(a);
            }
        }
        p->actions.clear();
        delete p;
    }
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
