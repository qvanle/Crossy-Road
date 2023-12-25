#ifndef ACTION_HPP
#define ACTION_HPP

#include <vector>

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
};

class Request : public Action
{
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
#endif 
