#include <frame.hpp>

/** 
 * @brief create a frame with a parent and a relative position
 *
 * @param par parent Frame 
 * @param rel relative position and size in percentage (0.0f to 1.0f)
**/ 

Frame::Frame(Frame* par, Rectangle rel)
{
    parent = nullptr;
    if(par == nullptr) 
    {
        throw std::runtime_error("Frame::Frame(Frame* par, fRect rel): par is nullptr");
        return ;
    }
    parent = par;
    relative[0] = rel.x;
    relative[1] = rel.y;
    relative[2] = rel.width;
    relative[3] = rel.height;

    parent->addSubframe(this);

    updateFrame();
}
/** 
 * @brief clone a frame
 * 
 * @param self Frame frame to clone
**/ 
Frame::Frame(Frame* self)
{
    parent = nullptr;
    if(self == nullptr) 
    {
        throw std::runtime_error("Frame::Frame(Frame* self): self is nullptr");
        return ;
    }
    parent = self->parent;
    relative = self->relative;
    frame = self->frame;
    for(auto& i : self->subframes)
    {
        subframes.push_back(i);
    }
}
/** 
 * @brief create a frame with a position and size
 * 
 * This is a root frame
 *
 * @param rec position and size in pixel
 *
**/
Frame::Frame(Rectangle rec)
{
    parent = nullptr;
    frame = rec;
    parent = nullptr;
    relative = {1, 1, 1, 1};
}

