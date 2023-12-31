#ifndef REQUEST_HPP
#define REQUEST_HPP 

namespace REQUEST 
{
    enum ID 
    {
        INVALID,
        NONE,
        CHANGE_INF,
        POP_INF,
        POP_THEN_CHANGE_INF,
        DELAY, 
        LOSE,
    };
}

namespace DIFFICULTY 
{
    enum ID 
    {
        INVALID,
        EASY,
        NORMAL,
        HARD,
        INSANE,
        NIGHTMARE,
    };
}
#endif 

