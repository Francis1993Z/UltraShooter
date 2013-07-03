#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include<sstream>

class Hud
{
    public:
        Hud(unsigned short p_life, unsigned long p_score, sf::Font p_font, sf::Vector2f p_tailleFenetre);
        void updateLife(unsigned short n_life);
        void updateScore(unsigned long n_score);
        void setSizeWindow(sf::Vector2f n_sizeWindow);
        sf::Text getLife();
        sf::Text getScore();
        ~Hud();
    protected:
    private:
        void setPositionHud();
        std::stringstream ss;
        sf::Vector2f sizeWindow;
        sf::Font font;
        sf::Text t_life;
        sf::Text t_score;
};

#endif // HUD_H
