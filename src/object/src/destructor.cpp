#include <object.hpp>


Object::~Object()
{
    for (auto &stroke : strokes)
    {
        delete stroke.stroke;
    }
    strokes.clear();

}
