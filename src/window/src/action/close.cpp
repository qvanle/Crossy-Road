#include <window.hpp>

CloseAction::CloseAction(Window* window) : Action(1)
{
    win = window;
}

void CloseAction::execute()
{
    win->status = false;
    doneExecute();
}
