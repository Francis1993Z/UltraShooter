#ifndef TEXTFIELD_INCLUDED_HPP
#define TEXTFIELD_INCLUDED_HPP

#include <SFML/Graphics.hpp>

#include <string>

#include "Widget.hpp"

class TextField : public Widget
{
public:
    TextField(int p_posX, int p_posY, int p_id);
    void draw();
    sf::FloatRect getCollisionBox() const;
    void setSurvolSouris(bool p_survol);
    void setClicSouris(bool p_clic);
    void codeKeyPressed(int code);
    std::string getText() const;
    ~TextField();
protected:
private:
    sf::RectangleShape champs;
    sf::Text contenuChamps;
    std::basic_string<sf::Uint32> str;
};

#endif // TEXTFIELD_INCLUDED_HPP
