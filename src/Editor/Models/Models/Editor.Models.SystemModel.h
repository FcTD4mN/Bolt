#pragma once


#include "Editor.Models.ModelBase.h"


#include <QAbstractItemModel>


namespace nCore::nECS::nCore { class cSystem; }


namespace  nQt {
namespace  nModels {


class  cSystemModel :
    public cModelBase
{
    Q_OBJECT

public:
    typedef cModelBase tSuperClass;

public:
    virtual ~cSystemModel();
    cSystemModel( ::nCore::nECS::nCore::cSystem* iSystem, QObject* iParent = 0 );
    cSystemModel( cSystemModel& iRef );

public:
    // Interface overrides
        // Read
    virtual  Qt::ItemFlags flags( const QModelIndex& iIndex ) const override;

public:
    virtual  void  BuildData() override;

private:
    ::nCore::nECS::nCore::cSystem*    mSystem;
};

} //nQt
} //nModels

