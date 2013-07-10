#include <iostream>

#include "MusicManager.hpp"

using namespace std;
using namespace sf;

MusicManager::MusicManager(int volume)
    :volume(volume)
{

}

MusicManager::~MusicManager()
{
    for(list<CustomSound *>::iterator it = lEventSounds.begin(); it != lEventSounds.end(); ++it) // On parcorus la liste des sons disponibles pour régler leur volume
        delete *it;
}

/*
* Permet de jouer une musique complète à partir d'un fichier (thème musical du niveau)
*/
void MusicManager::playTheme(string themePath)
{

    if(!theme.openFromFile(themePath))
        cout << "Fichier theme " << themePath << " introuvable !" << endl;

    theme.setVolume(volume);

    theme.setLoop(true);

    theme.play();

}

/*
* Permet de jouer un son court (tir, collision etc...) en ne chargent qu'une seule fois le son désiré à partir du fichier
*/
void MusicManager::playEvent(string eventPath)
{
    list<CustomSound *>::iterator itSound = lEventSounds.begin(); // On se place au début de la liste des sons

    for(;itSound != lEventSounds.end(); ++itSound) // On parcours la liste des sons disponibles
    {
        if((*itSound)->getSource() == eventPath)
        {
            if((*itSound)->getStatus() == SoundSource::Playing)
                return;
            else
            {
                (*itSound)->setVolume(volume);
                (*itSound)->play();

                return;
            }
        }
    }

    lEventSounds.push_back(new CustomSound(eventPath));
}

void MusicManager::setVolume(int volume)
{
    this->volume = volume;

    theme.setVolume(volume);

    for(list<CustomSound *>::iterator it = lEventSounds.begin(); it != lEventSounds.end(); ++it) // On parcorus la liste des sons disponibles pour régler leur volume
        (*it)->setVolume(volume);
}

int MusicManager::getVolume() const
{
    return theme.getVolume();
}

