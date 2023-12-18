#include <random.hpp>

#include <chrono>


RandomEngine::RandomEngine()
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    engine.seed(seed);
}

RandomEngine::RandomEngine(unsigned int seed)
{
    engine.seed(seed);
}

RandomEngine::~RandomEngine()
{
}

int RandomEngine::randInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}

double RandomEngine::randDouble(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(engine);
}

char RandomEngine::randChar(char min, char max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}

std::string RandomEngine::randString(int length, char min, char max)
{
    std::string str;
    for (int i = 0; i < length; i++)
    {
        str += randChar(min, max);
    }
    return str;
}

std::string RandomEngine::randInt2String(int length, int min, int max)
{
    std::string str;
    for (int i = 0; i < length; i++)
    {
        str += std::to_string(randInt(min, max));
    }
    return str;
}

std::string RandomEngine::randString(int length, bool haveDigit, bool haveLower, bool haveUpper, bool haveSpecial)
{
    std::string str;
    std::string digit = "0123456789";
    std::string lower = "abcdefghijklmnopqrstuvwxyz";
    std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string special = "!@#$%^&*()_+{}|:<>?~`-=[]\\;',./\"";
    std::string all = digit + lower + upper + special;
    if (haveDigit)
    {
        str += digit;
    }
    if (haveLower)
    {
        str += lower;
    }
    if (haveUpper)
    {
        str += upper;
    }
    if (haveSpecial)
    {
        str += special;
    }
    if (str.empty())
    {
        str = all;
    }
    std::string result;
    for (int i = 0; i < length; i++)
    {
        result += str[randInt(0, str.size() - 1)];
    }
    return result;
}
