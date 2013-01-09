#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <iostream>

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "LayerAnim.hpp"
#include "ImageManager.hpp"

#include "GlobalFunction.h"

/*
Une classe abstraite est une classe qui possède au moins une fonction virtuelle pure.
On ne peut pas créer d'objet à partir d'une classe abstraite.
*/

enum Behaviour {STANDBY, ATTACK, ESCAPE, FOLLOW};

class Entity//Abstraite
{
public:
//Un constructeur ne peut pas être virtuel.
//On ne peut pas appeler de fonctions virtuelles dans un constructeur. Si on le fait, le polymorphisme ne se fera pas.
virtual void sePresenter() const;//Fonction virtuel
//virtual double GetSurface() const=0;//Fonction virtuel pure
virtual ~Entity();//Destructeur virtuel - Un destructeur doit toujours être virtuel si on utilise le polymorphisme.

sf::Vector2f GetPosition() const;
Entity& getAdresse();

protected:
  std::vector<sf::Sprite> StandSprites;
  LayerAnim StandAnim;
int ID;
Entity *MyTarget;
Behaviour MyBehaviour;
    sf::RenderWindow *MyRenderWindow;
};

#endif // ENTITY_HPP_INCLUDED
