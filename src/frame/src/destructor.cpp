#include <frame.hpp>

Frame::~Frame()
{
    for(auto& subframe : subframes)
    {
        delete subframe;
    }
}
