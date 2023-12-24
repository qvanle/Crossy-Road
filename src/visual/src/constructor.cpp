#include <visual.hpp>


Visual::Visual(Texture2D* txtr, Frame* frame, Rectangle rect) : Frame(frame, rect)
{
    m_texture = std::shared_ptr<Texture2D>(txtr, [](Texture2D* texture){
        UnloadTexture(*texture);
        texture = nullptr;
    });
    resizeable = true;
    fitFrame();
}

Visual::Visual(Visual* visual) : Frame(visual)
{
    resizeable = false;
    m_texture = visual->m_texture;
    fitFrame();
}

Visual::Visual(Visual* visual, Rectangle rect) : Frame(visual, rect)
{
    resizeable = false;
    m_texture = visual->m_texture;
    fitFrame();
}

Visual::Visual(Visual* visual, Frame* frame, Rectangle rect) : Frame(frame, rect)
{
    resizeable = false;
    m_texture = visual->m_texture;
    fitFrame();
}
