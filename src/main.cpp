#include <SFML/Graphics.hpp>
#include "GameMockup/GameApplication.h"


#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "Math/Rectangle.h"

int main()
{
    cGameApplication* app = cGameApplication::App();
    app->Initialize();

    while( app->Window()->isOpen() )
    {
        sf::Event event;
        while( app->Window()->pollEvent( event ) )
        {
            app->HandleEvents( event );
        }

        app->Update();
        app->Window()->clear();
        app->Draw( app->Window() );
        app->Window()->display();
    }

    return 0;
}
