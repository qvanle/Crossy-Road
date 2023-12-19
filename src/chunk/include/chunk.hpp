#ifndef CHUNK_HPP
#define CHUNK_HPP 


#include <interface.hpp>

class Chunk : public Interface 
{
private: 

protected:

public: 
    Chunk(Frame*, Rectangle);
    Chunk(Chunk*);
    Chunk(Chunk*, Rectangle);
    Chunk(Chunk*, Frame*, Rectangle);
    ~Chunk();

    std::string linkContent(std::string path) override;
};

#endif 

