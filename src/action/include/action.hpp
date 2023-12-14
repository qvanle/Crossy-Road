#ifndef ACTION_HPP
#define ACTION_HPP

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

#endif 
