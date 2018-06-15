#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>

namespace nScreen { class cScreen; }

namespace nProject {

class cProject
{
public:
    ~cProject();
    cProject( const std::string& iProjectName, const std::string& iProjectFolder );

public:
    void Initialize();
    void Finalize();

public:
    // Screen
    void PushScreen( ::nScreen::cScreen* iScreen );
    void PopScreen();
    ::nScreen::cScreen*  CurrentScreen();

public:
    // Access/Get
    int  ResolutionWidth() const;
    int  ResolutionHeight() const;
    int  LimitFramerate() const;

    void  SetResolution( int iWidth, int iHeight );
    void  SetLimitFramerate( int iFramerate );

    const std::string&  Name() const;

public:
    // EDITOR
    int                     ScreenCount();
    ::nScreen::cScreen*     ScreenAtIndex( int iIndex );
    void                    RemoveScreenAtIndex( int iIndex );

//public:
//    void Update( unsigned int iDeltaTime );
//    void Draw( sf::RenderTarget* iRenderTarget );

public:
    // Input/Output
    virtual  void SaveXML();
    virtual  void LoadXML( const std::string& iProjectName );

protected:
    std::string                         mProjectName;
    std::string                         mProjectFolder;
    std::vector< ::nScreen::cScreen* >  mScreenStack;

    int                                 mResolutionWidth;
    int                                 mResolutionHeight;
    int                                 mLimitFramerate;
};


} // namespace nApplication

