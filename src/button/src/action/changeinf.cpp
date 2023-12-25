#include <button.hpp>
#include <const/request.hpp>
changeInfRequest::changeInfRequest(std::string s) 
{
    interfaceName = s;
}

changeInfRequest::changeInfRequest(changeInfRequest* other) 
{
    interfaceName = other->interfaceName;
}

int changeInfRequest::isRequest() 
{
    return REQUEST::CHANGE_INF;
}

Action* changeInfRequest::clone() 
{
    return new changeInfRequest(this);
}

std::string changeInfRequest::getInterfaceName() 
{
    return interfaceName;
}
