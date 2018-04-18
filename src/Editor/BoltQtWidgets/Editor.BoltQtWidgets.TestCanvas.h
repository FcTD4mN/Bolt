#pragma once

#include "Editor.BoltQtWidgets.QSFMLCanvas.h"

#include <QtCore/QModelIndex>

namespace nApplication { class cEditorApplication; }
namespace nECS { class cEntity; }


class MyCanvas :
    public QSFMLCanvas
{
    Q_OBJECT

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
    void Build();

private:
    virtual void OnInit() override;
    virtual void OnUpdate() override;

    virtual void resizeEvent( QResizeEvent* iEvent ) override;
    virtual void paintEvent( QPaintEvent* ) override;

private:
    // Draw functions
    void  DrawSelections() const;

public:
    // Event overrides
    virtual void mousePressEvent( QMouseEvent *iEvent ) override;
    virtual void mouseMoveEvent( QMouseEvent *iEvent ) override;
    virtual void mouseReleaseEvent( QMouseEvent *iEvent ) override;
    virtual void mouseDoubleClickEvent( QMouseEvent *iEvent ) override;

public slots:
    void CurrentPrototypeChanged( const QModelIndex& iIndex );

signals:
    void  SelectionChanged( ::nECS::cEntity* iEntity );

private:
    ::nApplication::cEditorApplication* mEditorApp;
    QModelIndex                         mCurrentPrototypeEntitySelected;

    sf::Vector2i    mOriginPosition;
    sf::FloatRect   mSelectionBox; // Used to draw
    sf::RectangleShape mSelectionShape;
    eState          mState;

    std::vector< ::nECS::cEntity* > mEntitySelection;
};


