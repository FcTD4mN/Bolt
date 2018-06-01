#pragma once

#include <SFML/Audio.hpp>

namespace nSound {

sf::SoundBuffer Reverb( const sf::SoundBuffer& iBuffer, int iReverbDelay );
sf::SoundBuffer LowPassFilter( const sf::SoundBuffer& iBuffer, double iValue );


} // namespace nMath

