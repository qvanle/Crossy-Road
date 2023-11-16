#include <frame.hpp>

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

void Frame::unplug()
{
    if(parent == nullptr) return ;
    parent->removeSubframe(this);
    parent = nullptr;
}

void Frame::addSubframe(Frame* subframe)
{
    subframes.push_back(subframe);
}

void Frame::removeSubframe(Frame* subframe)
{
    for(auto& i : subframes)
    {
        if(i == subframe)
        {
            i = subframes.back();
            subframes.pop_back();
            return ;
        }
    }
}

bool Frame::isroot()
{
    return parent == nullptr;
}
