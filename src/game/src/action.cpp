#include <game.hpp>

Action* Game::runtimeEvent()
{
    return nullptr;
}

Action* Game::react()
{
    return Interface::react();
}
