#ifndef ACTION_HPP
#define ACTION_HPP

#include <vector>

class Action 
{
public:
    Action();
    Action(Action*);
    virtual ~Action() = default;

    virtual bool isRequest();
    virtual void execute() = 0;
    virtual Action* clone();
};

class PacketAction : public Action
{
private: 
    std::vector<Action*> actions;
public: 
    PacketAction();
    PacketAction(PacketAction*);
    ~PacketAction();
    void addAction(Action*);
    void execute() override;
    PacketAction* clone() override;
};
#endif 
