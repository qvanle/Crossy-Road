#include <visual.hpp>


Visual::Visual(Texture2D* txtr, Frame* frame, Rectangle rect) : Frame(frame, rect)
{
    m_texture = txtr;
    fitFrame();
}


