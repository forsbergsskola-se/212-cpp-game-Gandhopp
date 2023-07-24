#include "Vector.h"

#include <cmath>


void vector::normalize(float &x, float& y)
{
    const float magnitude = abs(sqrt(x*x + y*y));
    x = x/magnitude;
    y = y/magnitude;
}
vector::vector(float x, float y) : x{x},y{y}
{
    
}

