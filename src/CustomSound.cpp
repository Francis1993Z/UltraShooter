#include <iostream>

#include "CustomSound.hpp"

using namespace std;
using namespace sf;


CustomSound::CustomSound(string source)
    :source(source)
{
    if(!buffer.loadFromFile(source))
    {
        cout << "Fichier event " << source << " introuvable !" << endl;
        exit(5);
    }

    sound.setBuffer(buffer);
}

CustomSound::~CustomSound()
{

}

string CustomSound::getSource() const
{
    return source;
}

void CustomSound::play()
{
    sound.play();
}

void CustomSound::setVolume(int volume)
{
   sound.setVolume(volume);
}

SoundSource::Status CustomSound::getStatus() const
{
    return sound.getStatus();
}
