#ifndef GLOBALFUNCTION_H_INCLUDED
#define GLOBALFUNCTION_H_INCLUDED

#include "PreHeader.h"

extern "C"
{
///int myGlobalFunction(); // tells compiler that there is a function defined somewhere
float GetAngle(float, float, float, float);
float Distance(float, float, float, float);
float Distance_v2f(sf::Vector2f, sf::Vector2f);
}

#endif // GLOBALFUNCTION_H_INCLUDED
