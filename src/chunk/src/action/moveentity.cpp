#include <chunk.hpp>

moveEntityAction::moveEntityAction(Chunk* chunk) : chunk(chunk)
{
}

moveEntityAction::~moveEntityAction()
{
}

void moveEntityAction::execute()
{
    
    chunk->movingEntity();
}

Action* moveEntityAction::clone()
{
    return new moveEntityAction(chunk);
}
