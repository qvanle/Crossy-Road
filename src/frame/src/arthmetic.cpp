#include <frame.hpp>

void Frame::updateFrame(bool recursive)
{
    
    if(parent != nullptr)
    {
        frame.x = parent->getX() + relative[0] * parent->getW();
        frame.y = parent->getY() + relative[1] * parent->getH();
        frame.width = relative[2] * parent->getW();
        frame.height = relative[3] * parent->getH();
    }

    if(recursive)
    {
        for(auto& subframe : subframes)
        {
            subframe->updateFrame(true);
        }
    }
}

void Frame::moveTo(fPoint rel)
{
    if(parent == nullptr) return ;
    relative[0] = rel[0];
    relative[1] = rel[1];
    updateFrame(true);
}
void Frame::moveTo(int x, int y)
{
    if(parent != nullptr) return ;
    frame.x = x;
    frame.y = y;
    updateFrame(true);
}

void Frame::moveCenterTo(fPoint rel)
{
    if(parent == nullptr) return ;
    fPoint center = getCenter();
    relative[0] += rel[0] - center[0];
    relative[1] += rel[1] - center[1];
    updateFrame(true);
}

void Frame::moveCenterTo(int x, int y)
{
    if(parent != nullptr) return ;
    fPoint center = getCenter();
    frame.x += x - center[0];
    frame.y += y - center[1];
    updateFrame(true);
}

void Frame::moveBy(fPoint rel)
{
    if(parent == nullptr) return ;
    relative[0] += rel[0];
    relative[1] += rel[1];
    updateFrame(true);
}

void Frame::moveBy(int x, int y)
{
    if(parent != nullptr) return ;
    frame.x += x;
    frame.y += y;
    updateFrame(true);
}

void Frame::resize(fPoint rel)
{
    if(parent == nullptr) return ;
    relative[2] = rel[0];
    relative[3] = rel[1];
    updateFrame(true);
}

void Frame::resize(int w, int h)
{
    if(parent != nullptr) return ;
    frame.width = w;
    frame.height = h;
    updateFrame(true);
}

const Rectangle& Frame::getFrame() const
{
    return frame;
}

const fRect& Frame::getRelative() const
{
    return relative;
}

const fPoint& Frame::getCenter() const
{
    static fPoint resu; 
    if(parent == nullptr) 
        resu = {frame.x + frame.width / 2, frame.y + frame.height / 2};
    else 
        resu = {relative[0] + relative[2] / 2, relative[1] + relative[3] / 2};

    return resu;
}

const float& Frame::getX() const
{
    return frame.x;
}

const float& Frame::getY() const
{
    return frame.y;
}

const float& Frame::getW() const
{
    return frame.width;
}

const float& Frame::getH() const
{
    return frame.height;
}

Frame::operator Rectangle() const
{
    return frame;
}

Frame::operator fRect() const
{
    return relative;
}

Frame::operator iRect() const
{
    return {(int) frame.x, (int) frame.y, (int) frame.width, (int) frame.height};
}


