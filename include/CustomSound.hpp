#ifndef CUSTOMSOUND_HPP_INCLUDED
#define CUSTOMSOUND_HPP_INCLUDED

#include <SFML/Audio.hpp>

class CustomSound
{
    std::string source;

    sf::Sound sound;
    sf::SoundBuffer buffer;

public :

    CustomSound(std::string source);
    ~CustomSound();

    std::string getSource() const;

    void play();
    void setVolume(int volume);

    sf::SoundSource::Status getStatus() const;

};


#endif // CUSTOMSOUND_HPP_INCLUDED
