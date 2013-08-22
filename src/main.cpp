#include <iostream>
#include <cstdio>
#include <string>


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Engine.hpp"

using namespace std;
using namespace sf;

int main()
{
    cout<<"Ultra Shooter"<<endl;
    cout<<"Build date : "<<__DATE__<<" at "<<__TIME__<<endl;

    srand(time(0));

    Engine* engine;
    engine = Engine::getInstance();
    int exit_code = engine->Run();

    delete engine;

    return exit_code;
}
//J'ai mis des lignes de code que je voulais me rappler un peu partout dans le code
//Certaine choses écrites ne sont pas vraiment utilse pour l'instant mais je voulais m'en rappeler car ça pourrait servir.
/* code pour mettre à jour une position en fonction du mouvement et
 de la rotation d'une autre position
sf::Vector2f NewTurretPosition;
  NewTurretPosition.x=((cos(GetRotation()*M_PI/180)*hypo))+(centre - position hotspot sur image).x + position image dans monde 2D.x;
  NewTurretPosition.y=(-(sin(GetRotation()*M_PI/180)*hypo))+GetPosition().y;
  t_turret->SetPosition(NewTurretPosition);

(centre - position hotspot sur image) + position image dans monde 2D
