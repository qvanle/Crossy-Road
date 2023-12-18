#include <chunk.hpp>

Chunk::Chunk(Frame* frame, Rectangle rect) : Interface(frame, rect)
{
}

Chunk::Chunk(Interface* other) : Interface(other) 
{
}

Chunk::Chunk(Interface* other, Rectangle rect) : Interface(other, rect) 
{
}

Chunk::Chunk(Interface* other, Frame* frame, Rectangle rect) : Interface(other, frame, rect) 
{
}