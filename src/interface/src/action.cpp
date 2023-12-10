#include <interface.hpp>

Action* Interface::react()
{
    if(!isVisible()) return nullptr;

    for(auto i : containers) 
    {
        Action* action = i->react();
        if(action != nullptr) return action;
    }

    return nullptr;
}
