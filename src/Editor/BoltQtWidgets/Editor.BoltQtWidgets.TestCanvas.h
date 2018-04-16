#pragma once

#include "Editor.BoltQtWidgets.QSFMLCanvas.h"

#include <QtCore/QModelIndex>

namespace nApplication { class cEditorApplication; }


class MyCanvas :
    public QSFMLCanvas
{
public:
    enum eState
    {
        kIdle,
        kSelecting,
        kPanningCanvas
    };

public:
    typedef QSFMLCanvas tSuperClass;

public:
    MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size );
    MyCanvas( QWidget* Parent );

public:
    void SetEditorApp( ::nApplication::cEditorApplication* iEditorApp );

private:
    virtual void OnInit() override;
    virtual void OnUpdate() override;

    virtual void resizeEvent( QResizeEvent* iEvent ) override;
    virtual void paintEvent( QPaintEvent* ) override;

public:
    // Event overrides
    virtual void mousePressEvent( QMouseEvent *iEvent ) override;
    virtual void mouseMoveEvent( QMouseEvent *iEvent ) override;
    virtual void mouseReleaseEvent( QMouseEvent *iEvent ) override;
    virtual void mouseDoubleClickEvent( QMouseEvent *iEvent ) override;

public slots:
    void CurrentPrototypeChanged( const QModelIndex& iIndex );

private:
    ::nApplication::cEditorApplication* mEditorApp;
    QModelIndex                         mCurrentPrototypeEntitySelected;

    sf::Vector2i    mOriginPosition;
    QRect           mSelectionBox; // Used to draw
    eState          mState;
};


