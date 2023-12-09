#ifndef ACTION_HPP
#define ACTION_HPP

class Action 
{
private: 
    int repeat; 
protected: 
    void setRepeat(int);
    void doneExecute();
    Action(int);
public:
    Action();
    virtual ~Action() = default;
    virtual void execute() = 0;
    virtual void ForceEnd();
    virtual void Interrupt();
    int getRepeat() const;
    bool isInfinite() const;
    bool isFinished() const;

};

#endif 
