#include <interface.hpp>
#include <const/path/atb.hpp>

Interface::Interface(Frame* frame, Rectangle rect) : Container(frame, rect)
{
}

Interface::Interface(Interface* other) : Container(other)
{
}

Interface::Interface(Interface* other, Rectangle rect) : Container(other, rect)
{
}

Interface::Interface(Interface* other, Frame* frame, Rectangle rect) : Container(other, frame, rect)
{
}

void Interface::linkContent(std::string path)
{
    Container::linkContentAbsolute(PATB::INTERFACE_ + path);
}
