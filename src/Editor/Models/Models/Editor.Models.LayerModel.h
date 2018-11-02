#pragma once


#include "Editor.Models.ModelBase.h"


#include <QAbstractItemModel>


namespace nCore { namespace  nRender { class cLayer; } }


namespace  nQt {
namespace  nModels {


class  cLayerModel :
    public cModelBase
{
    Q_OBJECT

public:
    typedef cModelBase tSuperClass;

public:
    virtual ~cLayerModel();
    cLayerModel( ::nCore::nRender::cLayer* iEntity, QObject* iParent = 0 );
    cLayerModel( cLayerModel& iRef );

public:
    // Interface overrides
        // Read
    virtual  Qt::ItemFlags flags( const QModelIndex& iIndex ) const override;

public:
    virtual  void  BuildData() override;

private:
    ::nCore::nRender::cLayer* mLayer;
};

} //nQt
} //nModels
