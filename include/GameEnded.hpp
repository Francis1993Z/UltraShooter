#ifndef GAMEENDED_INCLUDED_HPP
#define GAMEENDED_INCLUDED_HPP

#include <SFML/Graphics.hpp>

#include "WidgetListener.hpp"
#include "TextField.hpp"
#include "Button.hpp"

class GameEnded : public WidgetListener
{
public:
    GameEnded();
    void action(Widget* widgetClique);
    void draw();
    void setActif(bool p_actif, bool gameOver);
    void enregistrerScoreJoueur();
    bool isActif() const;
    virtual ~GameEnded();
protected:
private:
    sf::RectangleShape fond;
    bool actif;
    TextField* champsPseudo;
    sf::Text titre;
    sf::Text messageInformatif;
    Button* ok;
};

#endif // GAMEENDED_INCLUDED_HPP
