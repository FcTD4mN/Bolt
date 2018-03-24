#pragma once


#include <GL/glew.h>


#include <iostream>
#include <string>
#include <fstream>


class cShader
{
public:
    // Construction / Destruction
    ~cShader();
    cShader();
    cShader( cShader const &iShader );
    cShader( std::string iVertexSource, std::string iFragmentSource );
    cShader& operator=( cShader const &iShader );

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

