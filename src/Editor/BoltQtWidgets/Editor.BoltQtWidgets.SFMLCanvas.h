#pragma once

#include <SFML/Graphics.hpp>

#include <QModelIndex>
#include <QWidget>
#include <QTimer>

namespace nApplication { class cEditorApplication; }
namespace nECS { class cEntity; }
namespace nQt { namespace nHUD { class cHudBase; } }
namespace nQt { namespace nModels { class cEntityModel; } }


class SFMLCanvas :
    public QWidget,
    public sf::RenderWindow
{
    Q_OBJECT

public:
    enum eState
    {
        kIdle,
        kSelecting,
        kPanningCanvas,
        kMoveEntity,
        kHandleHUD
    };

public:
    typedef QWidget tSuperClass;

public:
    SFMLCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0 );
    SFMLCanvas( QWidget* Parent );

public:
    void SetEditorApp( ::nApplication::cEditorApplication* iEditorApp );
    void Build();
    void ClearHUDs();

private:
    virtual void OnInit();
    virtual void OnUpdate();

    virtual void resizeEvent( QResizeEvent* iEvent ) override;
    virtual void paintEvent( QPaintEvent* ) override;
    virtual void showEvent( QShowEvent* )  override;
    virtual QPaintEngine* paintEngine() const override;

private:
    // Draw functions
    void  DrawSelections() const;
    void  GetEntitySelectionBox( sf::Vector2f* oPosition, sf::Vector2f* oSize, ::nECS::cEntity * iEntity ) const;

public:
    // Event overrides
    virtual void mousePressEvent( QMouseEvent *iEvent ) override;
    virtual void mouseMoveEvent( QMouseEvent *iEvent ) override;
    virtual void mouseReleaseEvent( QMouseEvent *iEvent ) override;
    virtual void mouseDoubleClickEvent( QMouseEvent *iEvent ) override;
    virtual void keyReleaseEvent( QKeyEvent* iEvent ) override;
    virtual void wheelEvent( QWheelEvent* iEvent ) override;

public slots:
    void CurrentPrototypeChanged( const QModelIndex& iIndex );
    void  EntityMoved( float iDeltaX, float iDeltaY );
    void  EntityScaled( float iDeltaW, float iDeltaH );

signals:
    void  SelectionChanged( ::nECS::cEntity* iEntity, ::nQt::nModels::cEntityModel* iModel );

private:
    sf::RenderWindow* mRenderWindow;

    ::nApplication::cEditorApplication* mEditorApp;
    QModelIndex                         mCurrentPrototypeEntitySelected;

    sf::Vector2i    mOriginPosition;
    sf::FloatRect   mSelectionBox; // Used to draw
    sf::RectangleShape mSelectionShape;
    eState          mState;

    QTimer mTimer;
    bool   mInitialized;

    std::vector< ::nQt::nHUD::cHudBase* >   mEntityHUDs;
    ::nQt::nHUD::cHudBase*                  mActiveHUD;
    ::nQt::nModels::cEntityModel*           mEditedEntityModel;
};


