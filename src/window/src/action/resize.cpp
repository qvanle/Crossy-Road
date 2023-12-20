#include <window.hpp>

resizeAction::resizeAction(Window* window, float x, float y)
{
    win = window;
    w = x;
    h = y;
}

void resizeAction::execute()
{
    win->UI.root_frame->resize(w, h);
}


