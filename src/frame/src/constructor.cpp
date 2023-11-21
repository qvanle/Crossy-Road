#include <frame.hpp>

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
    updateFrame();

    parent->addSubframe(this);
}

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
    for(auto& i : self->subframes)
    {
        subframes.push_back(i);
    }
}

Frame::Frame(Rectangle rec)
{
    parent = nullptr;
    frame = rec;
    parent = nullptr;
    relative = {1, 1, 1, 1};
}

