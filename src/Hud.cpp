#include "Hud.hpp"
#include "Engine.hpp"

using namespace std;
using namespace sf;

Hud::Hud(long life, unsigned long score, Player& m_player)
{

my_player=&m_player;
    font = *Engine::getInstance()->getLoadFiles()->getPoliceArial();
    sf::Vector2u screensize = Engine::getInstance()->getRenderWindow()->getSize();
    sizeWindow.x = (float)screensize.x;
    sizeWindow.y = (float)screensize.y;
        setPositionHud();
            updateLife(life);
    updateScore(score);
}

void Hud::updateLife(long n_Life)
{
    ss.str("");
    ss << n_Life;
    t_life.setString(ss.str());
    t_life.setFont(font);
    t_life.setCharacterSize(30);
    t_life.setColor(sf::Color::Red);
}

void Hud::updateScore(unsigned long n_Score)
{
    ss.str("");
    ss << n_Score;
    t_score.setString(ss.str());
    t_score.setFont(font);
    t_score.setCharacterSize(30);
    t_score.setColor(sf::Color::Red);
}

void Hud::setSizeWindow(sf::Vector2f n_sizeWindow)
{
    sf::Vector2u screensize = Engine::getInstance()->getRenderWindow()->getSize();
    sizeWindow.x = (float)screensize.x;
    sizeWindow.y = (float)screensize.y;
    setPositionHud();
}

void Hud::setPositionHud()
{
    sf::Vector2f converted_Hud_coord = Engine::getInstance()->getRenderWindow()->mapPixelToCoords(sf::Vector2i(0, 0), Engine::getInstance()->getRenderWindow()->getView());
    cout<<"converted_Hud_coord.x : "<<converted_Hud_coord.x<<" converted_Hud_coord.y : "<<converted_Hud_coord.y<<endl;
    t_score.setPosition(converted_Hud_coord);
    t_life.setPosition(converted_Hud_coord.x-t_life.getGlobalBounds().width, converted_Hud_coord.y);
}

void Hud::Update()
{
    updateScore(my_player->getVie());
    updateScore(my_player->getScore());
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
