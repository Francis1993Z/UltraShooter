#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "EntityWithWeapon.hpp"

class Player : public EntityWithWeapon
{
public:
Player(float X, float Y, sf::Color Couleur, float Rayon, float Bordure, sf::Color CouleurBordure, Weapon StartWeapon, sf::RenderWindow &m_App, ImageManager &m_ImgManager);
void ApplyVelocity(sf::Vector2f velocity);
void Update();
void Update(float x, float y);
void SetDelayAnimation(float NewDelay);
void UpdateEvent(sf::RenderWindow &f_App);
void AddPoint(int point);
void Death();

sf::Shape GetShape() const;
LayerAnim GetAnim() const;


bool Immunity() const;
    float GetRayon() const;
    int GetScore() const;
    int GetLife() const;
    //int GetWeapon() const;


private:

    bool IamImmune;
    float rayon, ImmuneTime;
    sf::Clock ImmunityClock;
    sf::Vector2f Velocity;
    sf::Shape PlayerShape;
    unsigned long Score;
    unsigned short Life;

  std::string PlayerName;

};

#endif
