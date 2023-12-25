#include <action.hpp>
#include <const/request.hpp>
#include <queue>
#include <iostream>

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


Request::Request() : Action()
{
}

Request::Request(Request* request) : Action(request)
{
}

int Request::isRequest()
{
    return 1;
}

Action* Request::clone()
{
    return new Request(this);
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
