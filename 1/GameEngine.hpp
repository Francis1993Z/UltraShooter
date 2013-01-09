#ifndef GAMEENGINE_HPP_INCLUDED
#define GAMEENGINE_HPP_INCLUDED

#include "PreHeader.h"
#include "GlobalFunction.h"

#include "ImageManager.hpp"

#include "Player.hpp"
#include "Bullet.h"
#include "Ennemi.h"
#include "HUD.hpp"

class GameEngine
{
  public :
  GameEngine(unsigned int LF, unsigned int HF, unsigned int BM);
 int Run();
int func();
  private :
      bool Running;
      sf::RenderWindow App;
        sf::Event Event;
        ImageManager ImgManager;
            //HUD *Interface;
int LargeurFenetre, HauteurFenetre;
    std::vector<Bullet> BulletArray;
    std::vector<Ennemi> EnnemiArray;

    sf::Clock Bouttontime;

    sf::Vector2f MousePosition;
};

#endif // GAMEENGINE_HPP_INCLUDED
