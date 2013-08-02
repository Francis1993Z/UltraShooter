#include "Wave.hpp"

using namespace std;

Wave::Wave()
{
}

Wave::~Wave()
{
}

void Wave::addEnnemy(string type, int number)
{
    wEnnemy e;

    e.type = type;
    e.number = number;

    lEnnemy.push_back(e);
}

void Wave::loadEnnemies(EnnemyFactory & factory)
{

    for(list<wEnnemy>::const_iterator it = lEnnemy.begin(); it != lEnnemy.end(); ++it)
        {
            factory.createEnnemies(it->type, it->number);
        }
}
