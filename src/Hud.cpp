#include "Hud.hpp"
#include "Engine.hpp"

using namespace std;
using namespace sf;

Hud::Hud(long life, unsigned long score)
{
    font = *Engine::getInstance()->getLoadFiles()->getPoliceArial();

    sf::Vector2u screensize = Engine::getInstance()->getRenderWindow()->getSize();
    sizeWindow.x = (float)screensize.x;
    sizeWindow.y = (float)screensize.y;

    fondBarreDeVie.setSize(sf::Vector2f(200.f, 15.f));
    fondBarreDeVie.setFillColor(sf::Color::Red);
    barreDeVie.setSize(sf::Vector2f(200.f, 15.f));
    barreDeVie.setFillColor(sf::Color::Green);

    updateLife(life);
    updateScore(score);
    setPositionHud();
}

void Hud::updateLife(long n_life)
{
    barreDeVie.setSize(Vector2f(200.f/1000*n_life, barreDeVie.getSize().y));
}

void Hud::updateScore(unsigned long n_score)
{
    ss.str("");
    ss << n_score;
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
    t_score.setPosition(converted_Hud_coord);
    sf::Vector2f converted_Hud_coord2 = Engine::getInstance()->getRenderWindow()->mapPixelToCoords(sf::Vector2i((sizeWindow.x-fondBarreDeVie.getGlobalBounds().width), 0), Engine::getInstance()->getRenderWindow()->getView());
    fondBarreDeVie.setPosition(converted_Hud_coord2.x-10, converted_Hud_coord2.y+5);
    barreDeVie.setPosition(converted_Hud_coord2.x-10, converted_Hud_coord2.y+5);
}

void Hud::Update()
{
    updateLife(Engine::getInstance()->getPlayer()->getVie());
    updateScore(Engine::getInstance()->getPlayer()->getScore());
}

void Hud::Move(float vx, float vy)
{
    t_score.move(vx, vy);
    fondBarreDeVie.move(vx, vy);
    barreDeVie.move(vx, vy);
}

void Hud::draw(){

    Engine::getInstance()->getRenderWindow()->draw(t_score);
    Engine::getInstance()->getRenderWindow()->draw(fondBarreDeVie);
    Engine::getInstance()->getRenderWindow()->draw(barreDeVie);
}

Hud::~Hud()
{

}
