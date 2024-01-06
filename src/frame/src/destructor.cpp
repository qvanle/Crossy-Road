#include <frame.hpp>

/** 
 * @brief destroy a frame
 * 
 * MUST NOT DELETE ANYTHING 
 * 
 **/

Frame::~Frame()
{
    for(auto i : subframes) 
    {
        i->parent = nullptr;
    }
    unplug();
}
