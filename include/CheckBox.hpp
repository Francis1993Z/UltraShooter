#ifndef CHECKBOX_H_INCLUDED
#define CHECKBOX_H_INCLUDED

#include "Widget.hpp"

class CheckBox : public Widget
{
    public:
        CheckBox(sf::Vector2i p_pos, std::string p_text, int p_group);
        void draw();
        sf::FloatRect getCollisionBox() const;
        void setSurvolSouris(bool p_survol);
        void setClicSouris(bool p_clic);
        void codeKeyPressed(int code);
        bool isTickedOff() const;
        void setTickedOff(bool p_tickedOff);
        virtual ~CheckBox();
    protected:
    private:
        sf::Font font;
        sf::Text text;
        sf::Texture texture;
        sf::Texture textureSurvol;
        sf::Texture textureClic;
        sf::Sprite sprite;
        bool tickedOff;
};

#endif // CHECKBOX_H_INCLUDED
