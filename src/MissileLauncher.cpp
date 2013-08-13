#include "MissileLauncher.hpp"

#include "Engine.hpp"

using namespace std;
using namespace sf;

MissileLauncher::MissileLauncher(Entity const& my_user, bool p_tirIllimity, unsigned int p_ammunitions):Weapon(p_tirIllimity, p_ammunitions)
{
    user=&my_user;
    fire_intervale = 500.00f;
    needRefresh=false;//?
}


void MissileLauncher::fire()
{
    if((tirIllimity || (!tirIllimity && ammunitions > 0)) && fire_intervale_clock.getElapsedTime().asMilliseconds() >= fire_intervale)
        {
            if(!tirIllimity){

                --ammunitions;
            }
        }
}
