#include "Qt.Models.TreeWrapper.h"


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


cTreeWrapperNode::cTreeWrapperNode( eType iType, void* iData, cTreeWrapperNode* iParent ) :
    mParent( iParent ),
    mDataType( iType ),
    mDataPointer( iData )
{
}


// ======================================================================
// ============================================================ Hierarchy
// ======================================================================


int
cTreeWrapperNode::ChildrenCount() const
{
    return  mChildren.size();
}


cTreeWrapperNode*
cTreeWrapperNode::ChildAtColumn( int iColumn )
{
    return  mChildren[ iColumn ];
}


cTreeWrapperNode*
cTreeWrapperNode::Parent()
{
    return  mParent;
}


void
cTreeWrapperNode::AddChild( eType iType, void* iData )
{
    mChildren.push_back( new cTreeWrapperNode( iType, iData, this ) );
}


// ======================================================================
// ================================================================= Data
// ======================================================================


void*
cTreeWrapperNode::Data()
{
    return  mDataPointer;
}


cTreeWrapperNode::eType
cTreeWrapperNode::DataType()
{
    return  mDataType;
}

} //nModels
} //nQt

