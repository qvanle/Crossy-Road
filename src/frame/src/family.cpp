#include <frame.hpp>
#include <algorithm>


/** 
 * @brief attach a frame to a parent by relative position
 * 
 * @param par parent frame 
 * @param rel relative position and size in percentage (0.0f to 1.0f)
 * 
 **/
void Frame::plug(Frame* par, fRect rel)
{
    if(par == nullptr) 
    {
        throw std::runtime_error("Frame::plug(Frame* par, fRect rel): par is nullptr");
        return ;
    }
    parent = par;
    relative = rel;
    updateFrame();

    parent->addSubframe(this);
}

/** 
 * @brief attach a frame to a parent by old relative position
 * 
 * @param par parent frame 
 * 
 **/
void Frame::plug(Frame* par)
{
    if(par == nullptr) 
    {
        throw std::runtime_error("Frame::plug(Frame* par): par is nullptr");
        return ;
    }
    parent = par;
    updateFrame();

    parent->addSubframe(this);
}

/** 
 * @brief detach a frame from its parent
 * 
 **/
void Frame::unplug()
{
    if(parent == nullptr) return ;
    parent->removeSubframe(this);
    parent = nullptr;
}

/** 
 * @brief Add a subframe to this frame 
 * 
 * When unplug a subframe, parent frame will call this function, so you shouldn't call it
 *
 * @param subframe subframe to add
 * 
 **/
void Frame::addSubframe(Frame* subframe)
{
    subframes.push_back(subframe);
}

/** 
 * @brief Remove a subframe from this frame 
 * 
 * When destroy a subframe that have parent frame, this function is called, so you shouldn't call it
 *
 * @param subframe subframe to remove
 * 
 **/
void Frame::removeSubframe(Frame* subframe)
{
    int i = subframes.size() - 1;
    while(i >= 0 && subframes.size())
    {
        while(!subframes.empty() && subframes.back() == subframe)
            subframes.pop_back();
        i = std::min(i, (int) subframes.size() - 1);
        if(!subframes.empty() && subframes[i] == subframe)
        {
            subframes[i] = subframes.back();
            subframes.pop_back();
        }
    }
}

/** 
 * @brief return true if this frame is root
 * 
 **/
bool Frame::isroot()
{
    return parent == nullptr;
}
