#include <visual.hpp>


void Visual::draw()
{
    if(m_texture == nullptr) return ;
    Rectangle rec = getFrame();
    // draw texture 
    DrawTexture(*m_texture, rec.x, rec.y, WHITE);
}
