#include <window.hpp>

CloseAction::CloseAction(Window* window)
{
    win = window;
}

void CloseAction::execute()
{
    win->Wcontent.status = false;
}
