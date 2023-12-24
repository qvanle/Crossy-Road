#include <button.hpp>

ButtonImage:: ~ButtonImage()
{
    for(auto &action : actions)
    {
        delete action;
    }
}