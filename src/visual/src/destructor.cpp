#include <visual.hpp>

Visual::~Visual()
{
    if(m_texture != nullptr)
        UnloadTexture(*m_texture);
    delete m_texture;
}
