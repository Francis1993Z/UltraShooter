#include "Hud.hpp"
#include "iostream"

using namespace std;
using namespace sf;

Hud::Hud(unsigned short life, unsigned int score, sf::Font p_font, Vector2f p_sizeWindow):font(p_font), sizeWindow(p_sizeWindow)
{

    updateLife(life);
    updateScore(score);
    setPositionHud();
}

void Hud::updateLife(unsigned short n_Life)
{

    ss.str("");
    ss << n_Life;
    t_life.setString(ss.str());
    t_life.setFont(font);
    t_life.setCharacterSize(30);
    t_life.setColor(sf::Color::Red);
    //setPositionHud();
}

void Hud::updateScore(unsigned int n_Score)
{

    ss.str("");
    ss << n_Score;
    t_score.setString(ss.str());
    t_score.setFont(font);
    t_score.setCharacterSize(30);
    t_score.setColor(sf::Color::Red);
    //setPositionHud();
}

void Hud::setSizeWindow(sf::Vector2f n_sizeWindow)
{

    sizeWindow = n_sizeWindow;
    setPositionHud();
}

void Hud::setPositionHud()
{
    t_score.setPosition(0,0);
    t_life.setPosition(sizeWindow.x-t_life.getGlobalBounds().width, 0);
}

void Hud::Move(float vx, float vy)
{
    t_score.move(vx, vy);
    t_life.move(vx, vy);
}

sf::Text Hud::getLife()
{

    return t_life;
}

sf::Text Hud::getScore()
{

    return t_score;
}

Hud::~Hud()
{

}
