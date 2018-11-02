#pragma once

#include "Editor.Models.ModelBase.h"

#include <QAbstractItemModel>

namespace nCore::nProject { class cProject; }

namespace  nQt {
namespace  nModels {

class  cProjectPropertiesModel :
    public cModelBase
{
    Q_OBJECT

public:
    typedef cModelBase tSuperClass;

public:
    virtual ~cProjectPropertiesModel();
    cProjectPropertiesModel( ::nCore::nProject::cProject* iProject, QObject* iParent = 0 );
    cProjectPropertiesModel( cProjectPropertiesModel& iRef );

public:
    // Interface overrides
        // Read
    virtual  Qt::ItemFlags flags( const QModelIndex& iIndex ) const override;

public:
    virtual  void  BuildData() override;

private:
    ::nCore::nProject::cProject* mProject;
};

} //nQt
} //nModels
