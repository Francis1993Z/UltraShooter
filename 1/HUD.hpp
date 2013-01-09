#ifndef HUD_HPP_INCLUDED
#define HUD_HPP_INCLUDED

#include <iostream>
#include <cstdio>
#include <string>

#include <SFML/Graphics.hpp>

#include "Player.hpp"

class HUD
{
    public:
HUD(Player *User, sf::Vector2f Initial_Position, sf::RenderWindow &m_App);
    sf::String GetLifeString() const;
    sf::String GetScoreString() const;
    sf::String GetGameOverString() const;
    sf::String GetWeaponString() const;
    void Update();
    bool ShowIndicatorX() const;
    bool ShowIndicatorY() const;
    bool ShowGameOver() const;
    sf::Shape GetIndicatorShapeX() const;
    sf::Shape GetIndicatorShapeY() const;


    private:
    sf::Font Info_Font;
    sf::String Life, Score, GameOver, Weapon;
    sf::Shape RectOutX,RectOutY;
    bool ShowOutScreenPositionIndicatorX, ShowOutScreenPositionIndicatorY, gameover;
    char text_Life[150], text_Score[150], GameOvertxt[12], text_Weapon[50];
    unsigned int LargeurWindow, HauteurWindow;
     sf::RenderWindow *MyRenderWindow;
Player *m_user, *m_selected;
};


#endif // HUD_HPP_INCLUDED
