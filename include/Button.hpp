#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Widget.hpp"

#include <string>

class Button : public Widget
{
    public:
        Button(int p_posX, int p_posY, std::string p_text, int p_id);
        void draw();
        sf::FloatRect getCollisionBox() const;
        void setSurvolSouris(bool p_survol);
        void setClicSouris(bool p_clic);
        void codeKeyPressed(int code);
        virtual ~Button();
    protected:
    private:
        sf::Font font;
        sf::Text text;
        sf::Texture texture;
        sf::Texture textureSurvol;
        sf::Texture textureClic;
        sf::Sprite sprite;
        bool survol;
};

#endif // BUTTON_HPP_INCLUDED
