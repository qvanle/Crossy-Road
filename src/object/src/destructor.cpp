#include <object.hpp>


Object::~Object()
{
    for(auto &stroke : strokes)
    {
        delete stroke;
    }
    strokes.clear();

    for(auto &action : actions)
    {
        for(auto &a : action)
        {
            delete a;
        }
        action.clear();
    }
    actions.clear();
}
