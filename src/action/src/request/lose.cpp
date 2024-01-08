#include <request.hpp>
#include <const/request.hpp>

loseRequest::loseRequest(int score)
{
    args.num.clear();
    args.num.push_back(score);
}

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

ARGS& loseRequest::getArgs() 
{
    return args;
}
