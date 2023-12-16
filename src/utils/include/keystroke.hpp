#ifndef KEYSTROKE_HPP 
#define KEYSTROKE_HPP 

#include <action.hpp>
#include <vector>
#include <string>

int toKey(std::string);

class KeyStroke 
{
private: 
    std::vector<int> key;
    std::vector< Action* > action;
    int id;
public: 
    KeyStroke();
    KeyStroke(std::vector<int>);
    ~KeyStroke();

    int size();
    void add(unsigned char);
    void setAction(std::vector<Action*>);
    void addAction(Action*);
    void chooseAction(int);
    int getCurrent(int);
    void nextAction();

    Action* react();
};

#endif
