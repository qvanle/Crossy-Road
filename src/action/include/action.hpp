#ifndef ACTION_HPP
#define ACTION_HPP

#include <vector>
#include <string>

struct ARGS 
{
    std::vector<std::string> str;
    std::vector<int> num;
    std::vector<void*> addr;
    ARGS() = default;
    ~ARGS() = default;

    std::string getInterfaceName();
};
extern ARGS NONE_ARGS;
class Action 
{
public:
    Action();
    Action(Action*);
    virtual ~Action() = default;

    virtual int isRequest();
    virtual bool isPackage();
    virtual void execute();
    virtual Action* clone();
    virtual std::vector<Action*> unpack();
    virtual ARGS& getArgs();
};

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

class PacketAction : public Action
{
private: 
    std::vector<Action*> actions;
public: 
    PacketAction();
    PacketAction(PacketAction*);
    ~PacketAction();
    bool isPackage() override;
    void addAction(Action*);
    void addAction(PacketAction*);
    std::vector<Action*> unpack() override;
    void execute() override;
    PacketAction* clone() override;
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
#endif 
