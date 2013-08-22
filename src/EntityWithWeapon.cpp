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

bool EntityWithWeapon::isTirIllimity() const{

    return my_weapon.at(actual_weapon)->isTirIllimity();
}

unsigned int EntityWithWeapon::getAmmunitions() const{

    return my_weapon.at(actual_weapon)->getAmmunitions();
}

EntityWithWeapon::~EntityWithWeapon()
{
    for(vector<Weapon *>::iterator it = my_weapon.begin(); it != my_weapon.end(); ++it)
        delete *it;
}


sf::Vector2f EntityWithWeapon::searchhotspot(sf::Image tmpimg)
{

            sf::Vector2f turret_pos;
//Recherche des pixels de centrage
  for(unsigned int i=0; i<my_sizef.x; i++)
    {
      for(unsigned int j=0; j<my_sizef.y; j++)
        {
          sf::Color tmpcolor = tmpimg.getPixel(i, j);
          if(tmpcolor==sf::Color(255,0,0))//Affection de la position de la turret
            {
              turret_pos.x=i;
              turret_pos.y=j;
            }
        }
    }

    return turret_pos;
}
