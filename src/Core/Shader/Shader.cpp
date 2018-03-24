#include "Shader.h"


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cShader::~cShader()
{
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}


cShader::cShader() :
    m_vertexID(0),
    m_fragmentID(0),
    m_programID(0),
    m_vertexSource(),
    m_fragmentSource()
{
}


cShader::cShader( cShader const &iShader )
{
    m_vertexSource = iShader.m_vertexSource;
    m_fragmentSource = iShader.m_fragmentSource;
    Load();
}


cShader::cShader( std::string iVertexSource, std::string iFragmentSource ) :
    m_vertexID(0),
    m_fragmentID(0),
    m_programID(0),
    m_vertexSource( iVertexSource ),
    m_fragmentSource( iFragmentSource )
{
}


cShader& cShader::operator=( cShader const &iShader )
{
    m_vertexSource = iShader.m_vertexSource;
    m_fragmentSource = iShader.m_fragmentSource;

    Load();

    return *this;
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Public Interface


bool cShader::Load()
{
    // Destruction before rebuild
    if(glIsShader(m_vertexID) == GL_TRUE)
        glDeleteShader(m_vertexID);

    if(glIsShader(m_fragmentID) == GL_TRUE)
        glDeleteShader(m_fragmentID);

    if(glIsProgram(m_programID) == GL_TRUE)
        glDeleteProgram(m_programID);


    // Compilation
    if(!CompileShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;

    if(!CompileShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    // Program creation
    m_programID = glCreateProgram();


    // Attach shader to ID
    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    // Binding inputs
    glBindAttribLocation(m_programID, 0, "in_Vertex");
    glBindAttribLocation(m_programID, 1, "in_Color");
    glBindAttribLocation(m_programID, 2, "in_TexCoord0");

    // Linking program
    glLinkProgram(m_programID);

    // Check
    GLint error(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &error);

    // Error Handling
    if( error != GL_TRUE )
    {
        GLint errorSize(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &errorSize);
        char *errorCode = new char[errorSize + 1];

        // Collect error info
        glGetShaderInfoLog(m_programID, errorSize, &errorSize, errorCode );
        errorCode[errorSize] = '\0';

        // Print error
        std::cout << errorCode << std::endl;

        // Free
        delete[] errorCode;
        glDeleteProgram(m_programID);

        return false;
    }
    else
    {
        return true;
    }
}


bool cShader::CompileShader( GLuint &iShader, GLenum iType, std::string const &iSourceFile )
{
    // Creation
    iShader = glCreateShader( iType );

    // Checking
    if( iShader == 0 )
    {
        std::cout << "Error, wrong shader type (" << iType << ")" << std::endl;
        return false;
    }

    // Reading stream
    std::ifstream file( iSourceFile.c_str() );

    // Error Handling
    if(!file)
    {
        std::cout << "Error, cannot find source file: " << iSourceFile << std::endl;
        glDeleteShader( iShader );

        return false;
    }

    // Stream to string
    std::string ligne;
    std::string codeSource;

    // Reading
    while( getline( file, ligne ) )
        codeSource += ligne + '\n';

    // Closing file
    file.close();

    // Source code cstr
    const GLchar* sourcecstr = codeSource.c_str();

    // Sending source to shader
    glShaderSource( iShader, 1, &sourcecstr, 0 );

    // Compiling shader
    glCompileShader( iShader );

    // Compile check
    GLint compilerror( 0 );
    glGetShaderiv( iShader, GL_COMPILE_STATUS, &compilerror );

    // Error handling
    if( compilerror != GL_TRUE )
    {
        // Error size
        GLint errorSize( 0 );
        glGetShaderiv( iShader, GL_INFO_LOG_LENGTH, &errorSize );

        // Mem Alloc
        char *error = new char[ errorSize+ 1 ];


        // Get error info
        glGetShaderInfoLog( iShader, errorSize, &errorSize, error );
        error[ errorSize ] = '\0';

        // Print error
        std::cout << error << std::endl;

        // Free
        delete[] error;
        glDeleteShader( iShader );

        return false;
    }
    else
    {
        return true;
    }
}


// Getter

GLuint cShader::getProgramID() const
{
    return m_programID;
}
