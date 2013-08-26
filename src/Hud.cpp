#include "Hud.hpp"
#include "Engine.hpp"

using namespace std;
using namespace sf;

Hud::Hud()
{
    font = *Engine::getInstance()->getLoadFiles()->getPoliceArial();

    sf::Vector2u screensize = Engine::getInstance()->getRenderWindow()->getSize();
    sizeWindow.x = (float)screensize.x;
    sizeWindow.y = (float)screensize.y;

    t_score.setFont(font);
    t_score.setCharacterSize(30);
    t_score.setColor(sf::Color::Red);

    fondBarreDeVie.setSize(sf::Vector2f(200.f, 15.f));
    fondBarreDeVie.setFillColor(sf::Color::Red);
    barreDeVie.setSize(sf::Vector2f(200.f, 15.f));
    barreDeVie.setFillColor(sf::Color::Green);

    symboleWeapon = new Sprite();

    t_ammunitions.setFont(font);
    t_ammunitions.setCharacterSize(20);
    t_ammunitions.setColor(sf::Color::Red);
}

void Hud::init(long n_life, int p_vieMaxPlayer, unsigned long n_score, Texture* p_symboleWeapon, bool p_tirIllimity, unsigned int p_ammunitions){

    updateLife(n_life, p_vieMaxPlayer);
    updateScore(n_score);
    updateActualWeapon(p_symboleWeapon, p_tirIllimity, p_ammunitions);
    setPositionHud();
}

void Hud::updateLife(long n_life, int p_vieMaxPlayer)
{
    barreDeVie.setSize(Vector2f(200.f/p_vieMaxPlayer*n_life, barreDeVie.getSize().y));
}

void Hud::updateScore(unsigned long n_score)
{
    ss.str("");
    ss << n_score;
    t_score.setString(ss.str());
}

void Hud::updateActualWeapon(Texture* p_symboleWeapon, bool p_tirIllimity, unsigned int p_ammunitions){

    symboleWeapon->setTexture(*p_symboleWeapon);
    updateAmmunitions(p_tirIllimity, p_ammunitions);
}

void Hud::updateAmmunitions(bool p_tirIllimity, unsigned int p_ammunitions){

    if(!p_tirIllimity){

        ss.str("");
        ss << p_ammunitions;
        t_ammunitions.setString(ss.str());
    }
    else{

        t_ammunitions.setString("illimity");
    }
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
    sf::Vector2f converted_Hud_coord3 = Engine::getInstance()->getRenderWindow()->mapPixelToCoords(sf::Vector2i((sizeWindow.x-symboleWeapon->getGlobalBounds().width), (sizeWindow.y-symboleWeapon->getGlobalBounds().height)), Engine::getInstance()->getRenderWindow()->getView());
    symboleWeapon->setPosition(converted_Hud_coord3.x-10, converted_Hud_coord3.y-10);
    t_ammunitions.setPosition(symboleWeapon->getPosition().x, symboleWeapon->getPosition().y+symboleWeapon->getGlobalBounds().height-t_ammunitions.getGlobalBounds().height);
}

void Hud::Move(float vx, float vy)
{
    cout<<"move!"<<endl;
    t_score.move(vx, vy);
    fondBarreDeVie.move(vx, vy);
    barreDeVie.move(vx, vy);
    symboleWeapon->move(vx, vy);
    t_ammunitions.move(vx, vy);
}

void Hud::draw(){

    Engine::getInstance()->getRenderWindow()->draw(t_score);
    Engine::getInstance()->getRenderWindow()->draw(fondBarreDeVie);
    Engine::getInstance()->getRenderWindow()->draw(barreDeVie);
    Engine::getInstance()->getRenderWindow()->draw(*symboleWeapon);
    Engine::getInstance()->getRenderWindow()->draw(t_ammunitions);
}

Hud::~Hud()
{
    delete symboleWeapon;
}
