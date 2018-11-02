#pragma once

#include <SFML/Graphics.hpp>

namespace  nQt {
namespace  nHUD {

class  cSnapGrid
{

public:
    ~cSnapGrid();
    cSnapGrid( int iWidth, int iHeight );

public:
    void  Width( int iWidth );
    void  Height( int iHeight );
    int   Width() const;
    int   Height() const;
    void  Visible( bool iVisible );
    bool  Visible();

public:
    virtual  void Draw( sf::RenderTarget* iRenderTarget );

protected:
    int  mWidth;
    int  mHeight;
    bool mVisible;
};

} //nQt
} //nModels
