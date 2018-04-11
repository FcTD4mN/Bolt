#include "Core.Volumetric.SparseOctree.Data.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include <SFML/OpenGL.hpp>


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template<eLod2N LOD,typename Atomic>
inline cData<LOD,Atomic>::~cData()
{
    mROMSConfig = 0; // Non-Owning
    mParent = 0; // Non-Owning
}


template<eLod2N LOD,typename Atomic>
inline cData<LOD,Atomic>::cData( cROMSChunk< LOD, Atomic >*  iParent, const cROMSConfig * iROMSConfig ) :
    mROMSConfig( iROMSConfig ), // Non-Owning
    mParent( iParent ) // Non-Owning
{
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------ Template Data Container Accessors


template< eLod2N LOD, typename Atomic >
inline  eLod2N  cData< LOD, Atomic >::LODLevel()  const
{
    return  LOD;
}


template< eLod2N LOD, typename Atomic >
inline  tSize  cData< LOD, Atomic >::Size()  const
{
    return  tSize( LODLevel() );
}


template<eLod2N LOD,typename Atomic>
inline  float cData<LOD,Atomic>::Sizef() const
{
    return  float( Size() );
}


template< eLod2N LOD, typename Atomic >
inline  tVolume  cData< LOD, Atomic >::Capacity()  const
{
    return  mCapacity;
}


template< eLod2N LOD, typename Atomic >
inline  const  cROMSConfig&  cData< LOD, Atomic >::ROMSConfig()  const
{
    return  *mROMSConfig;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------- Render


template<eLod2N LOD,typename Atomic>
inline glm::vec3 cData<LOD,Atomic>::OctDebugColor()
{
    return glm::vec3( 1.0f, 1.0f, 1.0f );
}


template<eLod2N LOD,typename Atomic>
inline void cData<LOD,Atomic>::RenderOctDebug()
{
    glBegin( GL_LINES );
        glm::vec3 col = OctDebugColor();
        glColor3f( col.x, col.y, col.z );
        auto sizef = Sizef();
        glVertex3f( 0.f,    0.f,    0.f     );
        glVertex3f( sizef,  0.f,    0.f     );

        glVertex3f( 0.f,    0.f,    0.f     );
        glVertex3f( 0.f,    sizef,  0.f     );

        glVertex3f( 0.f,    0.f,    0.f     );
        glVertex3f( 0.f,    0.f,    sizef   );

        glVertex3f( sizef,  sizef,  sizef   );
        glVertex3f( 0.f,    sizef,  sizef   );

        glVertex3f( sizef,  sizef,  sizef   );
        glVertex3f( sizef,  0.f,    sizef   );

        glVertex3f( sizef,  sizef,  sizef   );
        glVertex3f( sizef,  sizef,  0.f     );

        glVertex3f( 0.f,    sizef,  0.f     );
        glVertex3f( sizef,  sizef,  0.f     );

        glVertex3f( 0.f,    sizef,  0.f     );
        glVertex3f( 0.f,    sizef,  sizef   );

        glVertex3f( sizef,  0.f,    0.f     );
        glVertex3f( sizef,  sizef,  0.f     );

        glVertex3f( sizef,  0.f,    0.f     );
        glVertex3f( sizef,  0.f,    sizef   );

        glVertex3f( 0.f,    0.f,    sizef   );
        glVertex3f( sizef,  0.f,    sizef   );

        glVertex3f( 0.f,    0.f,    sizef   );
        glVertex3f( 0.f,    sizef,  sizef   );
    glEnd();
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

