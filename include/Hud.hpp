#ifndef HUD_H
#define HUD_H


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include <sstream>

class Player;

class Hud
{

public:
    Hud(long p_life, unsigned long p_score, Player& m_player);

    void updateLife(long n_life);
    void updateScore(unsigned long n_score);
    void setSizeWindow(sf::Vector2f n_sizeWindow);
    void Move(float vx, float vy);
    void setPositionHud();
    void Update();
    sf::Text getLife();
    sf::Text getScore();

    ~Hud();

protected:
private:
Player* my_player;
    sf::Text t_life;
    sf::Text t_score;
    sf::Font font;

    sf::Vector2f sizeWindow;

    std::stringstream ss;
};

#endif // HUD_H
