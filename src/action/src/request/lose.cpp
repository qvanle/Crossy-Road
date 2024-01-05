#include <request.hpp>
#include <const/request.hpp>


loseRequest::loseRequest(loseRequest* other)
{
    args = other->args;
}

int loseRequest::isRequest() 
{
    return REQUEST::LOSE;
}

Action* loseRequest::clone() 
{
    return new loseRequest(this);
}

