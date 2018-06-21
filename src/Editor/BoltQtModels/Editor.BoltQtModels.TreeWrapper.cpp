#include "Editor.BoltQtModels.TreeWrapper.h"


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
	auto it = mChildren.begin();

	for( int i = 0; i< iIndex; ++i )
		++it;

	mChildren.insert( it, iNode );
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
        delete  mChildren[ iIndex ]; // iIndex will remain valid as we remove -> everythong shifts left
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

