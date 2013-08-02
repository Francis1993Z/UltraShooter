#ifndef WAVE_HPP_INCLUDED
#define WAVE_HPP_INCLUDED

#include <list>
#include <string>
#include <iostream>

#include "EnnemyFactory.hpp"

struct wEnnemy
{
    std::string type;
    int number;

};

class Wave
{
    std::list<wEnnemy> lEnnemy;

public :

    Wave();
    ~Wave();

    void addEnnemy(std::string type, int number);
    void loadEnnemies(EnnemyFactory & factory);

};


#endif // WAVE_HPP_INCLUDED
