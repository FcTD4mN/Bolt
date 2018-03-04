#pragma once

#include <cpython/Python.h>
#include <functional>
#include <string>
#include <unordered_map>

namespace  nBoltScript
{


class  cBoltScriptEnvironment
{
private:
    typedef  void ( *tOutputRedirectionFunction )( const  std::string& );

public:
    // Construction/Destruction
    ~cBoltScriptEnvironment();
    cBoltScriptEnvironment( std::function<void( const  std::string& )> iOutputRedirectionFunction );
    cBoltScriptEnvironment( const  cBoltScriptEnvironment& ) = delete; // Not Allowed

public:
    // Singleton GTRUX accessor
    static cBoltScriptEnvironment* BoltScriptEnvironment();
    static void  DefaultOutputRedirectionFunction( const  std::string&  iStr );
    static void  ResetOutputRedirectionFunction();

public:
    // Public Processing Interface
    void  ProcessRawString( const  std::string&  iStr );
    void  Print( const  std::string&  iStr );
    void  SetOutputRedirectionFunction( std::function<void( const  std::string& )> iOutputRedirectionFunction );

public:
    // Public Register Interface
    void  RegisterFunction( const  std::string&  iStr, std::function< void( void ) > iFPtr );

private:
    // Data Members
    std::function<void( const  std::string& )>  mOutputRedirectionFunction;
    std::unordered_map< std::string, std::function< void(void) > > mVoidFuncVoid;
};


// Wrapping accessor
cBoltScriptEnvironment*  Env();


/* Python wrapper for BoltScriptEnvironment redirected print */
static PyObject*
PyBoltPrint(PyObject *self, PyObject *args)
{
    const char *command;
    int sts = 0;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;

    std::string str = command;
    Env()->Print( command );
    return Py_BuildValue("i", sts);
}

static PyMethodDef PyBoltMethods[] = {
    {"PyBoltPrint", PyBoltPrint, METH_VARARGS,
     "Python wrapper for BoltScriptEnvironment redirected print."},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef PyBoltModule = {
    PyModuleDef_HEAD_INIT, "PyBolt", NULL, -1, PyBoltMethods,
    NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_PyBolt(void)
{
    return PyModule_Create(&PyBoltModule);
}


}  // namespace  nBoltScript

