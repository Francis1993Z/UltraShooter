#include "GlobalFunction.h"

using namespace std;
using namespace sf;

float GetAngle(float x1, float y1, float x2, float y2)
{
    float a=x2-x1;
    float o=y2-y1;
    float angle;
    angle = atan2(-o, a);
    return angle;
}

float Distance(float TheObj_X, float TheObj_Y, float MyObj_X, float MyObj_Y)
{
    float TCoteopposer=MyObj_Y-TheObj_Y;
    float TCoteadjacent=MyObj_X-TheObj_X;
    float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
    float Thypothenuse=sqrt(Tracinecarre);
    return Thypothenuse;
}

float Distance_v2f(sf::Vector2f o1, sf::Vector2f o2)
{
    float TCoteopposer=o2.y-o1.y;
    float TCoteadjacent=o2.x-o1.x;
    float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
    float Thypothenuse=sqrt(Tracinecarre);
    return Thypothenuse;
}
