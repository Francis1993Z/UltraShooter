#ifndef MENU_INCLUDED_HPP
#define MENU_INCLUDED_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "Button.hpp"
#include "WidgetListener.hpp"

class Menu : public WidgetListener
{
public:
    Menu(sf::Vector2u sizeWindow);
    virtual ~Menu();
    void draw();
    void action(int id);
    bool isActif() const;
    void afficher();
    void afficherScores();
protected:
private:
    sf::Texture texture;
    sf::Sprite sprite;
    bool actif;
    bool options;
    std::list<sf::Text> listeScores;

};

#endif // MENU_INCLUDED_HPP
