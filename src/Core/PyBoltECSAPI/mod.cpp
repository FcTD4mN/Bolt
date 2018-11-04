#include "mod.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.Application.Application.h"


namespace  nCore {
namespace  nPyBoltECSAPI {

/*
PyObject*
PyBoltECSAPIMethod_GetComponentByID( PyObject *self, PyObject *args )
{
    char* ent;
    char* comp;
    int val;

    if( !PyArg_ParseTuple( args, "ssi", &ent, &comp, &val ) )
        return  NULL;

    return Py_BuildValue( "i", 0 );
}


PyObject*
PyBoltECSAPIMethod_SetComponentByName( PyObject *self, PyObject *args )
{
    return Py_BuildValue( "i", 0 );
}



PyMethodDef PyBoltECSAPIMethods[] = {
    //{ "PyBoltPrint", test, METH_VARARGS, "doc" },
{ NULL, NULL, 0, NULL }
};

PyModuleDef PyBoltECSAPIModule = {
    PyModuleDef_HEAD_INIT, "PyBoltECSAPI", NULL, -1, PyBoltECSAPIMethods,
    NULL, NULL, NULL, NULL
};

PyObject*
PyInit_PyBoltECSAPI( void )
{
    return PyModule_Create( &PyBoltECSAPIModule );
}
*/


} // namespace nPyBoltECSAPI
} // namespace nCore

