#include <frame.hpp>

void Frame::updateFrame(bool recursive)
{
    
    if(parent != nullptr)
    {
        std::lock_guard<std::mutex> lock(mtx);
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
    if(isroot()) return ;
    mtx.lock();
    relative[0] = rel[0];
    relative[1] = rel[1];
    mtx.unlock();
    updateFrame(true);
}
void Frame::moveTo(int x, int y)
{
    if(parent != nullptr) return ;
    mtx.lock();
    frame.x = x;
    frame.y = y;
    mtx.unlock();
    updateFrame(true);
}

void Frame::moveCenterTo(fPoint rel)
{
    if(isroot()) return ;
    mtx.lock();
    fPoint center = getCenter();
    relative[0] += rel[0] - center[0];
    relative[1] += rel[1] - center[1];
    mtx.unlock();
    updateFrame(true);
}

void Frame::moveCenterTo(int x, int y)
{
    if(parent != nullptr) return ;
    mtx.lock();
    fPoint center = getCenter();
    frame.x += x - center[0];
    frame.y += y - center[1];
    mtx.unlock();
    updateFrame(true);
}

void Frame::moveBy(fPoint rel)
{
    if(isroot()) return ;
    mtx.lock();
    relative[0] += rel[0];
    relative[1] += rel[1];
    mtx.unlock();
    updateFrame(true);
}

void Frame::moveBy(int x, int y)
{
    if(parent != nullptr) return ;
    mtx.lock();
    frame.x += x;
    frame.y += y;
    mtx.unlock();
    updateFrame(true);
}

void Frame::resize(fPoint rel)
{
    if(isroot()) return ;
    mtx.lock();
    relative[2] = rel[0];
    relative[3] = rel[1];
    mtx.unlock();
    updateFrame(true);
}

void Frame::resize(int w, int h)
{
    if(parent != nullptr) return ;
    mtx.lock();
    frame.width = w;
    frame.height = h;
    mtx.unlock();
    updateFrame(true);
}

const Rectangle& Frame::getFrame() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return frame;
}

const fRect& Frame::getRelative() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return relative;
}

Frame* Frame::getParent() 
{
    std::lock_guard<std::mutex> lock(mtx);
    return parent;
}

void Frame::setRelative(fRect rel)
{
    mtx.lock();
    relative = rel;
    mtx.unlock();
    updateFrame(true);
}

const fPoint& Frame::getCenter() const
{
    std::lock_guard<std::mutex> lock(mtx);
    static fPoint resu; 
    if(isroot()) 
        resu = {frame.x + frame.width / 2, frame.y + frame.height / 2};
    else 
        resu = {relative[0] + relative[2] / 2, relative[1] + relative[3] / 2};

    return resu;
}

const float& Frame::getX() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return frame.x;
}

const float& Frame::getY() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return frame.y;
}

const float& Frame::getW() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return frame.width;
}

const float& Frame::getH() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return frame.height;
}

Frame::operator Rectangle() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return frame;
}

Frame::operator fRect() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return relative;
}

Frame::operator iRect() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return {(int) frame.x, (int) frame.y, (int) frame.width, (int) frame.height};
}


