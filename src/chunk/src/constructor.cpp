#include "const/path/atb.hpp"
#include <chunk.hpp>

Chunk::Chunk(Frame* frame, Rectangle rect) : Interface(frame, rect)
{

}

Chunk::Chunk(Chunk* other) : Interface(other)
{

}

Chunk::Chunk(Chunk* other, Rectangle rect) : Interface(other, rect)
{

}

Chunk::Chunk(Chunk* other, Frame* frame, Rectangle rect) : Interface(other, frame, rect)
{

}


std::string Chunk::linkContent(std::string path)
{
    return linkContentAbsolute(PATB::CHUNK_ + path);
}
