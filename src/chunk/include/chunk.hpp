#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <raylib.h>

#include <container.hpp>
#include <interface.hpp>

class Chunk : public Interface
{
private:
public:
	Chunk(Frame* frame, Rectangle rect);
    Chunk(Interface* other);
    Chunk(Interface* other, Rectangle rect);
    Chunk(Interface* other, Frame* frame, Rectangle rect);
	
	virtual ~Chunk() = default;
	
	Action* react() override;
	
	Action* getRuntimeEvent() override;
}	
#endif 
