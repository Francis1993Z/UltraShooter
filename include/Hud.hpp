#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include<sstream>

class Hud
{

public:
    Hud(unsigned short p_life, unsigned int p_score, sf::Font p_font, sf::Vector2f p_tailleFenetre);

    void updateLife(unsigned short n_life);
    void updateScore(unsigned int n_score);
    void setSizeWindow(sf::Vector2f n_sizeWindow);
    void Move(float vx, float vy);
    void setPositionHud();

    sf::Text getLife();
    sf::Text getScore();

    ~Hud();

protected:
private:

    sf::Text t_life;
    sf::Text t_score;
    sf::Font font;

    sf::Vector2f sizeWindow;

    std::stringstream ss;
};

#endif // HUD_H
