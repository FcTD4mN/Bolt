#include "Qt.DataModel.TreeWrapper.h"


namespace nQt {
namespace nModels {

// ======================================================================
// ============================================================ Hierarchy
// ======================================================================


cTreeWrapperNode::~cTreeWrapperNode()
{
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
    return  mChildren[ iIndex ];
}


cTreeWrapperNode*
cTreeWrapperNode::Parent()
{
    return  mParent;
}


void
cTreeWrapperNode::AddChild( cTreeWrapperNode* iChild )
{
    mChildren.push_back( iChild );
}


// ======================================================================
// ================================================================= Data
// ======================================================================


void*
cTreeWrapperNode::Data()
{
    return  mData;
}


eType
cTreeWrapperNode::DataType()
{
    return  mDataType;
}

} //nModels
} //nQt

