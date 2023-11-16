#include <frame.hpp>

Frame::Frame(Frame* par, fRect rel)
{
    if(par == nullptr) 
    {
        throw std::runtime_error("Frame::Frame(Frame* par, fRect rel): par is nullptr");
        return ;
    }
    parent = par;
    relative = rel;
    updateFrame();
}

Frame::Frame(Rectangle rec)
{
    frame = rec;
    parent = nullptr;
    relative = {1, 1, 1, 1};
}

