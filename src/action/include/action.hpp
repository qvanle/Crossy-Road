#ifndef ACTION_HPP
#define ACTION_HPP

#include <vector>

class Action 
{
private: 
    int repeat = 1; 
protected: 
    void doneExecute();
public:
    Action();
    Action(int);
    Action(Action*);
    virtual ~Action() = default;
    void setRepeat(int);

    virtual bool isRequest();
    virtual void execute() = 0;
    virtual void ForceEnd();
    virtual void Interrupt();
    virtual Action* clone();

    int getRepeat() const;
    bool isInfinite() const;
    bool isFinished() const;

};

class PacketAction : public Action
{
private: 
    std::vector<Action*> actions;
public: 
    PacketAction();
    PacketAction(int);
    PacketAction(PacketAction*);
    ~PacketAction();
    virtual void addAction(Action*);
    virtual void execute();
    virtual void ForceEnd();
    virtual void Interrupt();
    virtual PacketAction* clone();
};
#endif 
