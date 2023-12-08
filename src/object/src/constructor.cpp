#include <object.hpp>

Object::Object(Frame* f, Rectangle rel) : Container(f, rel)
{
}

Object::Object(Object* other) : Container(other)
{
}

Object::Object(Object* other, Rectangle rel) : Container(other, rel)
{
}

Object::Object(Object* other, Frame* f, Rectangle rel) : Container(other, f, rel)
{
}
