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
}


template<eLod2N LOD,typename Atomic>
inline cData<LOD,Atomic>::cData( const cROMSConfig * iROMSConfig ) :
    mROMSConfig( iROMSConfig ) // Non-Owning
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
    return  tSize( LOD() );
}


template<eLod2N LOD,typename Atomic>
inline float cData<LOD,Atomic>::Sizef() const
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

        for( float i=0.f; i <= 1.f; i+= Sizef() )
        {
            for( float j=0.f; j <= 1.f; j+= Sizef() )
            {
                for( float k=0.f; i <= 1.f; k+= Sizef() )
                {
                    glVertex3f( i, j, k );
                    for( float l=0.f; l <= 1.f; l+= Sizef() )
                    {
                        for( float m=0.f; m <= 1.f; m+= Sizef() )
                        {
                            for( float n=0.f; n <= 1.f; n+= Sizef() )
                            {
                                glVertex3f( l, m, n );
                            }
                        }
                    }
                }
            }
        }
    glEnd();
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

