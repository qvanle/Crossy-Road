#ifndef REQUEST_MY_HPP
#define REQUEST_MY_HPP

#include <action.hpp>

/**
 * @class Request
 *
 * @brief sends information to a higher, relevant entity
 * 
 * upgrades information to higher level
 * 
**/
class Request : public Action
{
protected: 
    ARGS args;
public: 
    Request();
    Request(Request*);
    ~Request() = default;

    int isRequest() override;
    virtual Action* clone() override;
};

class changeInfRequest : public Request
{
public: 
    changeInfRequest(std::string s);
    changeInfRequest(changeInfRequest*);
    ~changeInfRequest() = default;
    int isRequest() override;
    Action* clone() override;
    ARGS& getArgs() override;
};

/**
 * @class loseRequest
 *
 * @brief request sent when the player loses
 * 
**/
class loseRequest : public Request
{
public: 
    loseRequest() = default;
    loseRequest(loseRequest*);
    ~loseRequest() = default;
    int isRequest() override;
    Action* clone() override;
};

#endif 
