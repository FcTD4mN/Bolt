#pragma once


#ifdef WINDOWS
#include <cpython/Python.h>
#else
#include <Python.h>
#endif //WINDOWS


namespace nCore {
namespace nPyBoltECSAPI {


PyObject* PyInit_PyBoltECSAPI();


} // namespace nBoltScript
} // namespace nCore

