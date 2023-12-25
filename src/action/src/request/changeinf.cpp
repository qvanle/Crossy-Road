#include <action.hpp>
#include <const/request.hpp>
changeInfRequest::changeInfRequest(std::string s) 
{
    args.str.push_back(s);
}

changeInfRequest::changeInfRequest(changeInfRequest* other) 
{
    args = other->args;
}

int changeInfRequest::isRequest() 
{
    return REQUEST::CHANGE_INF;
}

Action* changeInfRequest::clone() 
{
    return new changeInfRequest(this);
}

ARGS& changeInfRequest::getArgs() 
{
    return args;
}
