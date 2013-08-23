#ifndef AUTOMATICWEAPON_HPP_INCLUDED
#define AUTOMATICWEAPON_HPP_INCLUDED

#include "Weapon.hpp"


class AutomaticWeapon : public Weapon
{
public:
    AutomaticWeapon(Entity const& my_user, bool p_tirIllimity, unsigned int p_ammunitions, sf::Vector2f pos);

    /// \brief Tire des projectiles
    ///
    /// Cette fonction tire des projectiles en fonction de la position de la souris
    /// Elle est tres utilise par les Player
    ///
    /// \return void

    void fire();

    /// \brief Tire des projectiles
    ///
    /// Cette fonction tire des projectile en fonction d'une position donne
    /// Elle est tres utilise par les entity controle par ordinateur
    ///
    /// \return void

    void fire(sf::Vector2f target_position);
};

#endif // AUTOMATICWEAPON_HPP_INCLUDED
