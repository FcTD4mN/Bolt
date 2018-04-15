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
    if( mChildren.size() > 0 )
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


QVariant
cTreeWrapperNode::DataAtColumn( int iColumn )
{
    return  mData[ iColumn ];
}


void
cTreeWrapperNode::AppendData( const QVariant & iData )
{
    mData.push_back( iData );
}


std::string
cTreeWrapperNode::Type() const
{
    return  "Invalid";
}

} //nModels
} //nQt

