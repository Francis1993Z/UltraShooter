#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class Button
{
    public:
        Button(int p_posX, int p_posY, std::string p_text);
        void draw();
        sf::FloatRect getCollisionBox() const;
        void setSurvolSouris(bool p_survol);
        virtual ~Button();
    protected:
    private:
        sf::Font font;
        sf::Text text;
        int id;
        sf::Texture texture;
        sf::Texture textureSurvol;
        sf::Texture textureClic;
        sf::Sprite sprite;
        bool survol;
};

#endif // BUTTON_HPP_INCLUDED
