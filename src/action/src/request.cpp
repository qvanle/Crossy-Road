#include <request.hpp>
#include <const/request.hpp>

Request::Request() : Action()
{
}

Request::Request(Request* request) : Action(request)
{
}

int Request::isRequest()
{
    return 1;
}

Action* Request::clone()
{
    return new Request(this);
}
