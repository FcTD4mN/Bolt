#pragma once


#include <GL/glew.h>


#include <iostream>
#include <string>
#include <fstream>


namespace nCore {
namespace nShader {


class cShader3D
{
public:
    // Construction / Destruction
    ~cShader3D();
    cShader3D();
    cShader3D( cShader3D const &iShader );
    cShader3D( std::string iVertexSource, std::string iFragmentSource );
    cShader3D& operator=( cShader3D const &iShader );

public:
    // Public Interface
    bool Load();
    bool CompileShader( GLuint &iShader, GLenum iType, std::string const &iSourceFile );
    GLuint getProgramID() const;


private:
    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;

};


} // namespace nShader
} // namespace nCore

