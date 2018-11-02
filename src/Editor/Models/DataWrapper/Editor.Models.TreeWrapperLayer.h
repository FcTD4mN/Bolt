#pragma once


#include "Editor.Models.TreeWrapper.h"


#include <QtCore>
#include <vector>


namespace nCore { namespace nRender { class cLayer; } }


namespace nQt {
namespace nModels {

class cTreeWrapperNodeLayer :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cTreeWrapperNodeLayer();
    cTreeWrapperNodeLayer( cTreeWrapperNode* iParent, ::nCore::nRender::cLayer* iLayer );

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
    ::nCore::nRender::cLayer* Layer();

private:
    ::nCore::nRender::cLayer* mLayer;
    ;
};


} // nModels
} // nQT