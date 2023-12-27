#ifndef REQUEST_MY_HPP
#define REQUEST_MY_HPP

#include <action.hpp>

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
