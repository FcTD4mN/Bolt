#include "Core.Sound.FX.h"

namespace nSound
{

sf::SoundBuffer Reverb( const sf::SoundBuffer & iBuffer, int iReverbDelayInMS )
{
    int ReverbDelayInSamples = int((double(iReverbDelayInMS) / 1000.0) * double(iBuffer.getSampleRate()));

    sf::SoundBuffer  reverbSound;
    const sf::Int16* bufferData = iBuffer.getSamples();
    sf::Int16* reverbBuffer = new sf::Int16[ iBuffer.getSampleCount() ];

    //memcpy( reverbBuffer, bufferData, iBuffer.getSampleCount() ); // Makes clicks at beginning and ending, dunno why

    // Manual memcpy
    for( int i = 0; i < iBuffer.getSampleCount(); ++i )
        reverbBuffer[ i ] = bufferData[ i ];

    for( int i = 0; i < iBuffer.getSampleCount() - ReverbDelayInSamples; ++i )
    {
        reverbBuffer[ i + ReverbDelayInSamples ] += sf::Int16(reverbBuffer[ i ] * 0.5);
    }

    reverbSound.loadFromSamples( reverbBuffer, iBuffer.getSampleCount(), iBuffer.getChannelCount(), iBuffer.getSampleRate() );
    delete[]  reverbBuffer;

    return  reverbSound;
}


sf::SoundBuffer
LowPassFilter( const sf::SoundBuffer & iBuffer, double iValue )
{
    sf::SoundBuffer  reverbSound;
    const sf::Int16* bufferData = iBuffer.getSamples();
    sf::Int16* reverbBuffer = new sf::Int16[ iBuffer.getSampleCount() ];

    double b = 1.0f - iValue;
    double z = 0;

    for( int n = 0; n < iBuffer.getSampleCount(); ++n )
    {
        z = ( bufferData[ n ] * b ) + ( z * iValue );
        reverbBuffer[ n ] = sf::Int16( z );
    }



    reverbSound.loadFromSamples( reverbBuffer, iBuffer.getSampleCount(), iBuffer.getChannelCount(), iBuffer.getSampleRate() );
    delete[]  reverbBuffer;

    return  reverbSound;
}

}

