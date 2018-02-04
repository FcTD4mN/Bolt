#include <SFML/Graphics.hpp>
#include "Application/Application.h"

int main()
{
    cApplication::App()->Initialize();
    sf::RenderWindow* window = cApplication::App()->Window();

    while( window->isOpen() )
    {
        sf::Event event;
        while( window->pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                window->close();
        }
         
    }

    return 0;
}
