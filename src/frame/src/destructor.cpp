#include <frame.hpp>

Frame::~Frame()
{
    unplug();
    for(Frame *& subframe : subframes)
    {
        delete subframe;
    }
}
