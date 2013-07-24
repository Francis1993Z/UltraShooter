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
        bool getJouer() const;
    protected:
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        bool jouer;
};

#endif // MENU_INCLUDED_HPP
