#pragma once

#include "Editor.Models.TreeWrapper.h"

#include <QtCore>
#include <vector>


namespace nCore { namespace nProject { class cProject; } }


namespace nQt {
namespace nModels {


class cTreeWrapperNodeProjectProperties :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cTreeWrapperNodeProjectProperties();
    cTreeWrapperNodeProjectProperties( cTreeWrapperNode* iParent, ::nCore::nProject::cProject* iProject );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  int        DataCount() const override;
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;

public:
    // Access/Get
    ::nCore::nProject::cProject* Project();

private:
    ::nCore::nProject::cProject* mProject;
};


} // nModels
} // nQT