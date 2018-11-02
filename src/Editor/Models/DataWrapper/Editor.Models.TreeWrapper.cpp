#include "Editor.Models.TreeWrapper.h"

#include "Core.Base.Utilities.h"

namespace nQt {
namespace nModels {

// ======================================================================
// ============================================================ Hierarchy
// ======================================================================


cTreeWrapperNode::~cTreeWrapperNode()
{
    for( auto& i : mChildren )
        delete  i;
}


cTreeWrapperNode::cTreeWrapperNode( cTreeWrapperNode* iParent ) :
    mParent( iParent )
{
    if( mParent )
        mParent->AddChild( this );
}


cTreeWrapperNode::cTreeWrapperNode() :
    mParent( 0 )
{
}


// ======================================================================
// ============================================================ Hierarchy
// ======================================================================


int
cTreeWrapperNode::ChildrenCount() const
{
    return  int(mChildren.size());
}


cTreeWrapperNode*
cTreeWrapperNode::ChildAtRow( int iRow )
{
    if( mChildren.size() > 0 && iRow < mChildren.size() )
        return  mChildren[ iRow ];
    return  0;
}


cTreeWrapperNode*
cTreeWrapperNode::Parent()
{
    return  mParent;
}


void
cTreeWrapperNode::AddChild( cTreeWrapperNode* iNode )
{
    mChildren.push_back( iNode );
    iNode->mParent = this;
}


void
cTreeWrapperNode::InsertChild( cTreeWrapperNode * iNode, int iIndex )
{
    iIndex = ::nCore::nBase::Clamp( iIndex, 0, int(mChildren.size() - 1) );

    mChildren.insert( mChildren.begin() + iIndex, iNode );
    iNode->mParent = this;
}


void cTreeWrapperNode::AddChild()
{
    new cTreeWrapperNode( this );
}


bool
cTreeWrapperNode::RemoveChildrenAtIndex( int iIndex, int iCount )
{
    if( iIndex < 0 || iIndex + iCount > mChildren.size() )
        return false;

    for( int i = 0; i < iCount; ++i )
    {
        //LEAK:
        // This will leak for now ...
        // Because when drag and dropping systems in tree views, at still refers the deleted element ...
        //TODO: see why/ learn to do a proper drag and drop in tree views
        //delete  mChildren[ iIndex ]; // iIndex will remain valid as we remove -> everythong shifts left
        mChildren.erase( mChildren.begin() + iIndex );
    }

    return  true;
}


bool
cTreeWrapperNode::RemoveChildrenAtIndexWithDelete( int iIndex, int iCount )
{
    if( iIndex < 0 || iIndex + iCount > mChildren.size() )
        return false;

    for( int i = 0; i < iCount; ++i )
    {
        delete  mChildren[ iIndex + i ];
        mChildren.erase( mChildren.begin() + iIndex );
    }

    return  true;
}



int
cTreeWrapperNode::IndexInParent() const
{
    for( int i = 0; i < mParent->mChildren.size(); ++i )
        if( mParent->mChildren[ i ] == this )
            return  i;

    return  -1;
}


// ======================================================================
// ================================================================= Data
// ======================================================================


int
cTreeWrapperNode::DataCount() const
{
    return  mData.size();
}


QVariant
cTreeWrapperNode::DataAtColumn( int iColumn )
{
    return  mData[ iColumn ];
}


bool
cTreeWrapperNode::SetData( int iIndex, const QVariant & iData )
{
    mData[ iIndex ] = iData;
    return  true;
}


void
cTreeWrapperNode::AppendData( const QVariant & iData )
{
    mData.push_back( iData );
}


bool cTreeWrapperNode::AppendColumns( int iIndex, int iCount )
{
    if( iIndex < 0 || iIndex > mData.size() )
        return  false;

    for( int i = 0; i < iCount; ++i )
        mData.insert( iIndex, QVariant() );

    for( auto child : mChildren )
        child->AppendColumns( iIndex, iCount );

    return  true;
}


bool cTreeWrapperNode::RemoveColumns( int iIndex, int iCount )
{
    if( iIndex < 0 || iIndex + iCount > mData.size() )
        return false;

    for( int i = 0; i < iCount; ++i )
        mData.erase( mData.begin() + iIndex );

    for( auto child : mChildren )
        child->RemoveColumns( iIndex, iCount );

    return true;
}


std::string
cTreeWrapperNode::Type() const
{
    return  "BaseNode";
}

} //nModels
} //nQt

