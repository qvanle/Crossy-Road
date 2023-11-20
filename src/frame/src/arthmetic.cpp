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
    updateFrame();
}

void Frame::moveCenterTo(fPoint rel)
{
    if(parent == nullptr) return ;
    fPoint center = getCenter();
    relative[0] += rel[0] - center[0];
    relative[1] += rel[1] - center[1];
    updateFrame();
}

void Frame::moveBy(fPoint rel)
{
    if(parent == nullptr) return ;
    relative[0] += rel[0];
    relative[1] += rel[1];
    updateFrame();
}

void Frame::resize(fPoint rel)
{
    if(parent == nullptr) return ;
    relative[2] = rel[0];
    relative[3] = rel[1];
    updateFrame();
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
    return {relative[0] + relative[2] / 2, relative[1] + relative[3] / 2};
}

const int& Frame::getX() const
{
    return frame.x;
}

const int& Frame::getY() const
{
    return frame.y;
}

const int& Frame::getW() const
{
    return frame.width;
}

const int& Frame::getH() const
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

