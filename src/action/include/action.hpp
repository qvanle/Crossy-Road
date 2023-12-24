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
    virtual bool isPackage();
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
    bool isPackage() override;
    void addAction(Action*);
    void addAction(PacketAction*);
    std::vector<Action*> unpack();
    void execute() override;
    PacketAction* clone() override;
};
#endif 
