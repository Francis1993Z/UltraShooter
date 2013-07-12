#ifndef WAVE_HPP_INCLUDED
#define WAVE_HPP_INCLUDED

#include <list>
#include <string>

typedef struct
{
    std::string type;
    int number;

} wEnnemy;

class Wave
{
    std::list<wEnnemy> lEnnemy;

public :

    Wave();
    ~Wave();

    void addEnnemy(std::string type, int number);

};


#endif // WAVE_HPP_INCLUDED
