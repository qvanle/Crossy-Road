#include <vector.hpp>

using namespace VECTOR2D;

float VECTOR2D::getAngle(fPoint v1)
{
    // arctan(y / x) 
    return atan2(v1[1], v1[0]);
}

float sqr(float x)
{
    return x * x;
}

float VECTOR2D::getAngle(fPoint v1, fPoint v2)
{
    // angle between 2 vector 
    // v1 * v2 = |v1| * |v2| * cos(angle)

    float dot = v1[0] * v2[0] + v1[1] * v2[1];
    float abs1 = sqrt(sqr(v1[0]) + sqr(v1[1]));
    float abs2 = sqrt(sqr(v2[0]) + sqr(v2[1]));
    return acos(dot / (abs1 * abs2));
}
