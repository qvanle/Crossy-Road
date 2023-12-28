#include <container.hpp>

bool Container::isOverlapping(fPoint point)
{
    Rectangle rec = getFrame();
    return (point[0] >= rec.x && point[0] <= rec.x + rec.width && point[1] >= rec.y && point[1] <= rec.y + rec.height);

}

bool Container::isOverlapping(Rectangle rec)
{
    Rectangle rec2 = getFrame();
    return (rec.x <= rec2.x + rec2.width && rec.x + rec.width >= rec2.x && rec.y <= rec2.y + rec2.height && rec.y + rec.height >= rec2.y);
}

bool Container::isOverlapping(Container* container)
{
    Rectangle rec = getFrame();
    Rectangle rec2 = container->getFrame();
    return (rec.x <= rec2.x + rec2.width && rec.x + rec.width >= rec2.x && rec.y <= rec2.y + rec2.height && rec.y + rec.height >= rec2.y);
}

float Container::OverlappingArea(Rectangle rec)
{
    Rectangle rec2 = getFrame();
    float x = std::max(rec.x, rec2.x);
    float y = std::max(rec.y, rec2.y);
    float w = std::min(rec.x + rec.width, rec2.x + rec2.width) - x;
    float h = std::min(rec.y + rec.height, rec2.y + rec2.height) - y;
    if(w < 0 || h < 0) return 0;
    return w * h;
}

float Container::OverlappingArea(Container* container)
{
    Rectangle rec = container->getFrame();
    Rectangle rec2 = getFrame();
    float x = std::max(rec.x, rec2.x);
    float y = std::max(rec.y, rec2.y);
    float w = std::min(rec.x + rec.width, rec2.x + rec2.width) - x;
    float h = std::min(rec.y + rec.height, rec2.y + rec2.height) - y;
    if(w < 0 || h < 0) return 0;
    return w * h;
}

bool Container::isCollide(Rectangle rec)
{
    Rectangle rec2 = getFrame();
    bool a1 = rec.x <= rec2.x && rec2.x <= rec.x + rec.width;
    bool a2 = rec2.x <= rec.x && rec.x <= rec2.x + rec2.width;
    bool b1 = rec.y <= rec2.y && rec2.y <= rec.y + rec.height;
    bool b2 = rec2.y <= rec.y && rec.y <= rec2.y + rec2.height;

    return (a1 || a2) && (b1 || b2);
}

bool Container::isCollide(Container* other)
{
    return isCollide(other->getFrame());
}
