#include <keystroke.hpp>
#include <raylib.h>
#include <string>
#include <iostream>

KeyStroke::KeyStroke()
{
    id = 0;
}

KeyStroke::KeyStroke(std::vector<int> k)
{
    key = k;
    id = 0;
}

KeyStroke::~KeyStroke()
{
    for(auto &a : action)
    {
        delete a;
    }
}

int KeyStroke::size()
{
    return key.size();
}

void KeyStroke::add(unsigned char k)
{
    key.push_back(k);
}
void KeyStroke::setAction(std::vector<Action*> a)
{
    action = a;
}

void KeyStroke::addAction(Action* a)
{
    action.push_back(a);
}

Action* KeyStroke::react()
{
    for(auto k : key)
    {
        if(!IsKeyDown(k)) return nullptr;
    }
    return action[id]->clone(); 
}
void KeyStroke::chooseAction(int i)
{
    id = i;
}

int KeyStroke::getCurrent(int i)
{
    return id;
}

void KeyStroke::nextAction()
{
    id = (id + 1) % action.size();
}


int toKey(std::string x)
{
    if(x.size() == 1) 
    {
        if(x[0] >= 'a' && x[0] <= 'z') 
            return x[0] - 'a' + KEY_A;
        if(x[0] >= 'A' && x[0] <= 'Z')
            return x[0] - 'A' + KEY_A;

        if(x[0] >= '0' && x[0] <= '9')
            return x[0] - '0' + KEY_ZERO;

        switch (x[0]) {
            case ' ':
                return KEY_SPACE;
            case '.':
                return KEY_PERIOD;
            case ',':
                return KEY_COMMA;
            case ';':
                return KEY_SEMICOLON;
            case '\'':
                return KEY_APOSTROPHE;
            case '/':
                return KEY_SLASH;
            case '\\':
                return KEY_BACKSLASH;
            case '-':
                return KEY_MINUS;
            case '=':
                return KEY_EQUAL;
            case '[':
                return KEY_LEFT_BRACKET;
            case ']':
                return KEY_RIGHT_BRACKET;
            case '`':
                return KEY_GRAVE;
            case '~':
                return KEY_GRAVE;
            case '!':
                return KEY_ONE;
            case '@':
                return KEY_ONE;
            case '#':
                return KEY_THREE;
            case '$':
                return KEY_FOUR;
            case '%':
                return KEY_FIVE;
            case '^':
                return KEY_SIX;
            case '&':
                return KEY_SEVEN;
            case '*':
                return KEY_EIGHT;
            case '(':
                return KEY_NINE;
            case ')':
                return KEY_ZERO;
            case '_':
                return KEY_MINUS;
            case '+':
                return KEY_EQUAL;
            case '{':
                return KEY_LEFT_BRACKET;
            case '}':
                return KEY_RIGHT_BRACKET;
            case ':':
                return KEY_SEMICOLON;
            case '"':
                return KEY_APOSTROPHE;
            case '<':
                return KEY_COMMA;
            case '>':
                return KEY_PERIOD;
            case '?':
                return KEY_SLASH;
        }
    }else 
    {
        if(x == "esc") return KEY_ESCAPE; if(x == "enter") return KEY_ENTER;
        if(x == "tab") return KEY_TAB;

        if(x == "shift") return KEY_LEFT_SHIFT;
        if(x == "control") return KEY_LEFT_CONTROL;
        if(x == "alt") return KEY_LEFT_ALT;
        if(x == "super") return KEY_LEFT_SUPER;

        if(x == "right") return KEY_RIGHT;
        if(x == "left") return KEY_LEFT;
        if(x == "down") return KEY_DOWN;
        if(x == "up") return KEY_UP;

        if(x == "leftshift") return KEY_LEFT_SHIFT;
        if(x == "leftcontrol") return KEY_LEFT_CONTROL;
        if(x == "leftalt") return KEY_LEFT_ALT;
        if(x == "leftsuper") return KEY_LEFT_SUPER;
        if(x == "rightshift") return KEY_RIGHT_SHIFT;
        if(x == "rightcontrol") return KEY_RIGHT_CONTROL;
        if(x == "rightalt") return KEY_RIGHT_ALT;
        if(x == "rightsuper") return KEY_RIGHT_SUPER;
        if(x == "menu") return KEY_MENU;

        if(x == "backspace") return KEY_BACKSPACE;
        if(x == "insert") return KEY_INSERT;
        if(x == "delete") return KEY_DELETE;
        if(x == "pause") return KEY_PAUSE;
        
        if(x == "f1") return KEY_F1;
        if(x == "f2") return KEY_F2;
        if(x == "f3") return KEY_F3;
        if(x == "f4") return KEY_F4;
        if(x == "f5") return KEY_F5;
        if(x == "f6") return KEY_F6;
        if(x == "f7") return KEY_F7;
        if(x == "f8") return KEY_F8;
        if(x == "f9") return KEY_F9;
        if(x == "f10") return KEY_F10;
        if(x == "f11") return KEY_F11;
        if(x == "f12") return KEY_F12;

        if(x == "pageup") return KEY_PAGE_UP;
        if(x == "pagedown") return KEY_PAGE_DOWN;
        if(x == "home") return KEY_HOME;
        if(x == "end") return KEY_END;
        if(x == "capslock") return KEY_CAPS_LOCK;
        if(x == "scrolllock") return KEY_SCROLL_LOCK;
        if(x == "numlock") return KEY_NUM_LOCK;
        if(x == "printscreen") return KEY_PRINT_SCREEN;
    }

    return 0;
}
