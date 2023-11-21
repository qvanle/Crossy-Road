#include <visual.hpp>

Visual::Visual(Texture2D* txtr, Frame* frame) : Frame(frame)
{
    m_texture = txtr;
}

Visual::Visual(Texture2D* txtr, Frame* frame, Rectangle rect) : Frame(frame, rect)
{
    m_texture = txtr;
}

Visual::Visual(Texture2D* txtr, Rectangle rect) : Frame(rect)
{
    m_texture = txtr;
}


