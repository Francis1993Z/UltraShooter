#include "EntityWithWeapon.hpp"

using namespace std;
using namespace sf;
/*
EntityWithWeapon::EntityWithWeapon(sf::Transformable const& my_Entity)
{
entity=&my_Entity;
}*/

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
/*
sf::Transformable EntityWithWeapon::getEntity() const
{
return entity;
}
*/
