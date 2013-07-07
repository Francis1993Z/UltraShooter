#ifndef GLOBALFUNCTIONS_H_INCLUDED
#define GLOBALFUNCTIONS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #include <errno.h>
    #define GetCurrentDir getcwd
 #endif

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

extern "C"
{
    ///int myGlobalFunction(); // tells compiler that there is a function defined somewhere
    float GetAngle(float, float, float, float);
    float GetAngle_v2f(sf::Vector2f vec1, sf::Vector2f vec2);
    float Distance(float, float, float, float);
    float Distance_v2f(sf::Vector2f, sf::Vector2f);
        std::string getCWD();
}

#endif // GLOBALFUNCTIONS_H_INCLUDED
