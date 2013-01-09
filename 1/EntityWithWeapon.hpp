#ifndef ENTITYWITHWEAPON_HPP_INCLUDED
#define ENTITYWITHWEAPON_HPP_INCLUDED

#define WEAPONS_LIST_LIMIT 10

#include "Entity.hpp"

#include "Bullet.h"

enum Weapon
 { MACHINEGUN = 0,
            SHOTGUN = 1,
            MISSILE = 2,
            ROCKET = 3,
            MULTIROCKET = 4,
            MINE = 5,
            LASER = 6,
            GRENADE = 7,
            RAILGRENADE = 8,
            NAILSGRENADE = 9
            };
/*
            struct UnlockedWeaponList
            {
           bool MACHINEGUN = false,
           bool SHOTGUN = false,
           bool MISSILE = false,
           bool ROCKET = false,
           bool MULTIROCKET = false,
           bool MINE = false,
           bool LASER = false,
           bool GRENADE = false,
           bool RAILGRENADE = false,
           bool NAILSGRENADE = false};
            }*/
typedef unsigned int WEAPON;

class EntityWithWeapon: public Entity
{
  public:
  //EntityWithWeapon();
EntityWithWeapon(Weapon StartWeapon);
  void ChangeWeapon(Weapon NewWeapon);
void NextWeapon();
void PreviousWeapon();
bool ReadyToShoot() const;
void Shoot(std::vector<Bullet> & bullet_array, sf::Vector2f MousePosition);

  protected:
  float DamageMulti;

float FireRate;
sf::Clock FireRateClock;
WEAPON CurrentWeapon;
bool UnlockedWeaponList[WEAPONS_LIST_LIMIT];
};

#endif // ENTITYWITHWEAPON_HPP_INCLUDED
