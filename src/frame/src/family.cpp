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
    mtx.lock();
    parent = par;
    relative = rel;
    mtx.unlock();
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
    mtx.lock();
    parent = par;
    mtx.unlock();
    updateFrame();

    parent->addSubframe(this);
}

/** 
 * @brief detach a frame from its parent
 * 
 **/
void Frame::unplug()
{
    if(isroot()) return ;
    mtx.lock();
    parent->removeSubframe(this);
    parent = nullptr;
    mtx.unlock();
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
    mtx.lock();
    subframes.push_back(subframe);
    mtx.unlock();
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
    mtx.lock();
    int i = subframes.size() - 1;
    auto it = std::find(subframes.begin(), subframes.end(), subframe);
    if(it != subframes.end())
        subframes.erase(it);
    mtx.unlock();
}

/** 
 * @brief return true if this frame is root
 * 
 **/
bool Frame::isroot() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return parent == nullptr;
}

void Frame::beginUpdate()
{
    mtx.lock();
}

void Frame::endUpdate()
{
    mtx.unlock();
}
