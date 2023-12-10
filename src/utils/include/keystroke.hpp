#ifndef KEYSTROKE_HPP 
#define KEYSTROKE_HPP 

#include <action.hpp>
#include <vector>

int toKey(std::string);

class KeyStroke 
{
    private: 
        std::vector<int> key;
        Action* action;
    public: 
        KeyStroke();
        KeyStroke(std::vector<int>);
        ~KeyStroke();

        int size();
        void add(unsigned char);
        void setAction(Action*);

        Action* react();
};

#endif
