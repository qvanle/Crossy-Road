#include <container.hpp>

changeImageAction::changeImageAction(Container* c, iPoint p)
{
    container = c;
    focus = p;
}

changeImageAction::changeImageAction(changeImageAction* c)
{
    container = c->container;
    focus = c->focus;
}

changeImageAction::~changeImageAction()
{
    container = nullptr;
}

void changeImageAction::execute()
{
    container->chooseImage(focus[0], focus[1]);
}

Action* changeImageAction::clone()
{
    return new changeImageAction(this);
}
