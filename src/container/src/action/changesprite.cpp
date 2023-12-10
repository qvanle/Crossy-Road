#include <container.hpp>

changeImageAction::changeImageAction(Container* c, iPoint p)
{
    container = c;
    focus = p;
    setRepeat(1);
}

changeImageAction::changeImageAction(changeImageAction* c)
{
    container = c->container;
    focus = c->focus;
    setRepeat(1);
}

changeImageAction::~changeImageAction()
{
    container = nullptr;
}

void changeImageAction::execute()
{
    container->chooseImage(focus[0], focus[1]);
    doneExecute();
}

void changeImageAction::ForceEnd()
{
}

void changeImageAction::Interrupt()
{
}

Action* changeImageAction::clone()
{
    return new changeImageAction(this);
}
