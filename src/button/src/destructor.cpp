#include <button.hpp>

ButtonImage:: ~ButtonImage()
{
    for(auto &action : actions)
    {
        delete action;
    }
    
    if(request != nullptr)
        delete request;
}