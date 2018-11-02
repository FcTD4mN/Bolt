#pragma once

#include "Editor.Widgets.QSFMLWidget.h"


#include <SFML/Graphics.hpp>

#include <QModelIndex>
#include <QWidget>
#include <QTimer>
#include <QStyledItemDelegate>

#include <set>
#include <memory>

namespace nCore { namespace nProject { class cProject; } }
namespace nCore  { namespace nECS { namespace nCore { class cEntity; } } }
namespace nQt { namespace nHUD { class cHudBase; } }
namespace nQt { namespace nHUD { class cSnapGrid; } }
namespace nQt { namespace nModels { class cEntityModel; } }
namespace nQt { namespace nModels { class cModelBase; } }
namespace nQt { namespace nModels { class cProjectHierarchyModel; } }

class  cEntityPropertyDelegate;


class CoreSFMLCanvas :
    public QSFMLWidget
{
    Q_OBJECT

public:
    enum eState
    {
        kIdle,
        kClickSelection,
        kRubberSelection,
        kPanningCanvas,
        kMoveEntity,
        kHandleHUD
    };

public:
    typedef QSFMLWidget tSuperClass;

public:
    ~CoreSFMLCanvas();
    CoreSFMLCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0 );
    CoreSFMLCanvas( QWidget* Parent );

public:
    void Build();
    void ClearHUDs();

private:
    virtual void OnInit() override;
    virtual void OnUpdate() override;
    virtual void OnDraw() override;

    virtual void resizeEvent( QResizeEvent* event ) override;
    virtual void showEvent( QShowEvent* event )  override;

private:
    // Draw functions
    void  DrawSelections() const;
    void  GetEntitySelectionBox( sf::Vector2f* oPosition, sf::Vector2f* oSize, ::nCore::nECS::nCore::cEntity * iEntity ) const;
    sf::Vector2f GetSizeFromEntity( ::nCore::nECS::nCore::cEntity* iEntity ) const;

public:
    // Event overrides
    virtual void mousePressEvent( QMouseEvent *iEvent ) override;
    virtual void mouseMoveEvent( QMouseEvent *iEvent ) override;
    virtual void mouseReleaseEvent( QMouseEvent *iEvent ) override;
    virtual void mouseDoubleClickEvent( QMouseEvent *iEvent ) override;
    virtual void keyReleaseEvent( QKeyEvent* iEvent ) override;
    virtual void wheelEvent( QWheelEvent* iEvent ) override;

public slots:
    void  ScreenEditionAsked( const QModelIndex& iIndex );
    void  CurrentPrototypeChanged( const QModelIndex& iIndex );
    void  ToggleGridVisible();
    void  SetSnapGridUp();

    // EntityEdition
    void  StartingEntityEdition();
    void  EntityMoved( float iDeltaX, float iDeltaY );
    void  EntityScaled( float iDeltaW, float iDeltaH );

    // Project
    void  ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel* iProject );

signals:
    void  selectionChanged( const std::vector< ::nCore::nECS::nCore::cEntity* >& iSelectedEntities );
    void  forceRefresh();

private:
    ::nCore::nProject::cProject* _Project();

private:
    ::nQt::nModels::cProjectHierarchyModel* mProjectModel;
    QModelIndex                             mCurrentPrototypeEntitySelected;


    sf::Vector2i                    mOriginPosition;
    std::vector< sf::Vector2f >     mEntitiesOriginalPositions;
    std::vector< sf::Vector2f >     mEntitiesOriginalSizes;
    sf::FloatRect                   mSelectionBox; // Used to draw
    sf::RectangleShape              mSelectionShape;
    eState                          mState;

    QTimer mTimer;
    bool   mInitialized;

    std::vector< ::nQt::nHUD::cHudBase* >           mEntityHUDs;
    ::nQt::nHUD::cHudBase*                          mActiveHUD;
    std::shared_ptr< ::nQt::nModels::cEntityModel > mEditedEntityModel;
    ::nQt::nHUD::cSnapGrid*                         mSnapGrid;

    bool                                            mNeedDuplication;
};

