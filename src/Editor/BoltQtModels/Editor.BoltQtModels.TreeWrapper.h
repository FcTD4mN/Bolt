#pragma once

#include <vector>

#include <QtCore>

namespace nQt {
namespace nModels {

class cTreeWrapperNode
{
public:
    ~cTreeWrapperNode();
    cTreeWrapperNode( cTreeWrapperNode* iParent );

public:
    // Hierarchy
    cTreeWrapperNode* Parent();
    int ChildrenCount() const;
    cTreeWrapperNode* ChildAtRow( int iRow );
    void AddChild( cTreeWrapperNode* iNode );

    int IndexInParent() const;

    // Data
    QVariant DataAtColumn( int iColumn );
    void AppendData( const QVariant& iData );

    // Type
    virtual std::string Type() const;

private:
    cTreeWrapperNode* mParent;
    std::vector< cTreeWrapperNode* > mChildren;

    QVariantList mData;
};

} // nModels
} // nQT