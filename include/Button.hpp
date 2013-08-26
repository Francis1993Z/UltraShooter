#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "Widget.hpp"

#include <string>

enum Language{En, Fr};

class Button : public Widget
{
public:
    Button(sf::Vector2i p_pos, std::string p_text, int p_group);
    void draw();
    sf::FloatRect getCollisionBox() const;
    void setSurvolSouris(bool p_survol);
    void setClicSouris(bool p_clic);
    void codeKeyPressed(int code);
    void addLanguage(Language language, std::string p_text);
    void setCurrentLanguage(Language language);
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
    std::string listeLanguages[2];
};

#endif // BUTTON_HPP_INCLUDED
