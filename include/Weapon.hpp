#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include "Entity.hpp"
#include "Bullet.hpp"


class Weapon
{
public:
    virtual void fire();//feu
    virtual void fire(sf::Vector2f target_position);//feu avec position de la cible
    virtual void refresh();//mise a jour
    virtual void update();
    bool isUpdatable() const;//permert de savoir si l'arme soit etre mise a jour
    virtual ~Weapon();
protected:
    int damage;//dommage inflige
    sf::Clock fire_intervale_clock;//temps ecoule a cahque tire
    float fire_intervale;//Itervale de temps spcecifique entre chaque projectile tirer
    const Entity* user;//Pointeur sur l'utilisateur de l'arme
    bool needRefresh;//Si l'arme a besoin d'être mise à jour dans la boucle principale
};
#endif // WEAPON_HPP_INCLUDED
