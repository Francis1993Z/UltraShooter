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
  NewTurretPosition.x=((cos(GetRotation()*M_PI/180)*hypo))+GetPosition().x;
  NewTurretPosition.y=(-(sin(GetRotation()*M_PI/180)*hypo))+GetPosition().y;
  t_turret->SetPosition(NewTurretPosition);

  inline float Hypothenuse(float a, float o)
{

     //a=fabs(a);
     //o=fabs(o);

  float tmp;
  tmp=(powf(a, 2))+(powf(o, 2));
  float hypothenuse=sqrt(tmp);
  if(a < 0 || o < 0) hypothenuse = hypothenuse - (hypothenuse*2);//Si hypo est negatif la racine le renvoi quand meme en positif,
  //donc s'il est a plus de la moitier de l'image on inverse le signe.
  //Ex : hypo=9 -> 9x2=18 -> 9-18=-9
  return hypothenuse;
}
*/
