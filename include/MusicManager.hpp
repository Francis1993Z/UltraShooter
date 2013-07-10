#ifndef MUSICMANAGER_HPP_INCLUDED
#define MUSICMANAGER_HPP_INCLUDED

#include <SFML/Audio.hpp>

#include <string>
#include <map>
#include <list>

#include "CustomSOund.hpp"

class MusicManager
{
    sf::Music theme; // Thème du niveau à jouer
    std::list<CustomSound> lEventSounds; // Liste des sons disponibles

    int volume; // Volume général de l'application (musique et sons)

public :

    MusicManager(int volume = 50);
    ~MusicManager();

    void playTheme(std::string themePath); // Permet de jouer une musique (thème musical du niveau)
    void playEvent(std::string eventPath); // Permet de jouer un son bref (tire, collision etc...).

    void setVolume(int volume); // Permet de régler le volume global du jeu (musique et sons).
    int getVolume() const; // Permet de récupérer le volume global du jeu.

};


#endif // MUSICMANAGER_HPP_INCLUDED
