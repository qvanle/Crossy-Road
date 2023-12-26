#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <string>

class RandomEngine 
{
private: 
    std::mt19937 engine;
public:
    RandomEngine();
    RandomEngine(unsigned int seed);
    ~RandomEngine();
    int randInt(int min = 0, int max = 1);
    double randDouble(double min = 0, double max = 1);
    char randChar(char min = 0, char max = 127);
    std::string randString(int length, char min, char max);
    std::string randInt2String(int length, int min = 0, int max = 9);
    std::string randString(int length, bool haveDigit = true, bool haveLower = true, bool haveUpper = true, bool haveSpecial = true);
};


#endif 
