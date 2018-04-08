
#include <vector>

namespace nQt {
namespace nModels {

class cTreeWrapperNode
{
private:
    enum eType
    {
        kEntity = 0,
        kComponent,
        kVariant
    };

public:
    ~cTreeWrapperNode();
    cTreeWrapperNode( eType iType, void* iData, cTreeWrapperNode* iParent );

public:
    // Hierarchy
    int ChildrenCount() const;
    cTreeWrapperNode* ChildAtColumn( int iColumn );
    cTreeWrapperNode* Parent();
    void AddChild( cTreeWrapperNode* iChild );

    // Data
    void* Data();
    eType DataType();

private:
    cTreeWrapperNode* mParent;
    std::vector< cTreeWrapperNode* > mChildren;

    eType mDataType;
    void* mDataPointer;
};

} // nModels
} // nQT