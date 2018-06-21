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
    cTreeWrapperNode();

public:
    // Hierarchy
    cTreeWrapperNode* Parent();
    int ChildrenCount() const;
    cTreeWrapperNode* ChildAtRow( int iRow );
    void AddChild( cTreeWrapperNode* iNode );
    void InsertChild( cTreeWrapperNode* iNode, int iIndex );
    virtual void AddChild(); // The add row interface

    virtual  bool RemoveChildrenAtIndex( int iIndex, int iCount );

    int IndexInParent() const;

    // Data
    int DataCount() const;
    QVariant DataAtColumn( int iColumn );
    virtual  bool SetData( int iIndex, const QVariant& iData );
    void AppendData( const QVariant& iData );

    bool AppendColumns( int iIndex, int iCount );
    bool RemoveColumns( int iIndex, int iCount );

    // Type
    virtual std::string Type() const;

protected:
    cTreeWrapperNode* mParent;
    std::vector< cTreeWrapperNode* > mChildren;

    QVariantList mData;
};

} // nModels
} // nQT