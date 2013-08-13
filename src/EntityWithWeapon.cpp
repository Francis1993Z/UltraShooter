#include "EntityWithWeapon.hpp"

using namespace std;
using namespace sf;

void EntityWithWeapon::change_Weapon(int delta)
{
    int weapon_size=(int)my_weapon.size();
    if(delta>0)
        {
            if(actual_weapon==weapon_size-1) actual_weapon=0;
            else actual_weapon++;
        }
    else if(delta<0)
        {
            if(actual_weapon==0) actual_weapon=weapon_size-1;
            else actual_weapon--;
        }
}

Texture* EntityWithWeapon::getSymboleActualWeapon(){

    return my_weapon.at(actual_weapon)->getSymbole();
}

EntityWithWeapon::~EntityWithWeapon()
{
    for(vector<Weapon *>::iterator it = my_weapon.begin(); it != my_weapon.end(); ++it)
        delete *it;
}
