#ifndef COUNT_DOWN_HPP
#define COUNT_DOWN_HPP

#include <chrono>

/**
 * @class CountDown
 *
 * @brief count the time a playthrough takes
 * 
**/
class CountDown 
{
private: 
    std::chrono::time_point<std::chrono::system_clock> start; 
    std::chrono::duration<double> elapsed_seconds;
    bool finished; 
public: 
    CountDown(int milliseconds);
    ~CountDown();
    int get();
    bool isFinished();
    void run();
};

#endif 
