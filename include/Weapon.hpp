#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include "Entity.hpp"
#include "Bullet.hpp"


class Weapon
{
public:
    Weapon(bool p_tirIllimity, unsigned int p_ammunitions;
    virtual void fire();//feu
    virtual void fire(sf::Vector2f target_position);//feu avec position de la cible
    virtual void refresh();//mise a jour
    virtual void update();
    bool isUpdatable() const;//permet de savoir si l'arme doit être mise a jour
    sf::Texture* getSymbole();
    bool isTirIllimity() const;
    unsigned int getAmmunitions() const;
    virtual ~Weapon();
protected:
    int damage;//dommages infligés
    sf::Clock fire_intervale_clock;//temps écoulé à chaque tir
    float fire_intervale;//Itervale de temps spcecifique entre chaque projectile tiré
    const Entity* user;//Pointeur sur l'utilisateur de l'arme
    bool needRefresh;//Si l'arme a besoin d'être mise à jour dans la boucle principale
    sf::Texture symbole;
    bool tirIllimity;
    unsigned int ammunitions;
};
#endif // WEAPON_HPP_INCLUDED
