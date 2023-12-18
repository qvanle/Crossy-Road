#include <window.hpp>

resizeAction::resizeAction(Window* window, float x, float y) : Action(1)
{
    win = window;
    w = x;
    h = y;
}

void resizeAction::execute()
{
    win->UI.root_frame->resize(w, h);
    doneExecute();
}


