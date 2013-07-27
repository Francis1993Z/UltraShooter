#include "GlobalFunctions.h"

inline float Distance(float TheObj_X, float TheObj_Y, float MyObj_X, float MyObj_Y)
{
    float TCoteopposer=MyObj_Y-TheObj_Y;
    float TCoteadjacent=MyObj_X-TheObj_X;
    float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
    float Thypothenuse=sqrt(Tracinecarre);

    return Thypothenuse;
}

inline float Distance_v2f(sf::Vector2f o1, sf::Vector2f o2)
{
    float TCoteopposer=o2.y-o1.y;
    float TCoteadjacent=o2.x-o1.x;
    float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
    float Thypothenuse=sqrt(Tracinecarre);

    return Thypothenuse;
}


inline float GetAngle(float x1, float y1, float x2, float y2)
{
    float a=x2-x1;
    float o=y2-y1;
    float angle;

    angle = atan2(-o, a);

    return angle;
}

inline float GetAngle(sf::Vector2f vec1, sf::Vector2f vec2)
{
    float a=vec2.x-vec1.x;
    float o=vec2.y-vec1.y;
    float angle;

    angle = atan2(-o, a);

    return angle;
}

bool fileExists(const char * path)
{
    FILE* fp = NULL;

    fp = fopen( path, "rb" );
    if( fp != NULL )
        {
            fclose( fp );
            return true;
        }

    return false;
}

int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}

std::string getCWD()
{
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
        {
            std::cout<<"Erreur, cwd not found : "<<errno<<std::endl;
        }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

    std::string d(cCurrentPath);
//std::cout<<"The current working directory is "<<cCurrentPath<<std::endl;
    return d;
}

