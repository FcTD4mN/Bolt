#pragma once


#include "Editor.Models.TreeWrapper.h"


#include <QtCore>
#include <vector>


namespace nCore { namespace nECS { namespace nCore { class cSystem; } } }

namespace nQt {
namespace nModels {

class cTreeWrapperNodeSystem :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cTreeWrapperNodeSystem();
    cTreeWrapperNodeSystem( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cSystem* iSystem );

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
    ::nCore::nECS::nCore::cSystem* System();

private:
    ::nCore::nECS::nCore::cSystem* mSystem;
    ;
};


} // nModels
} // nQT