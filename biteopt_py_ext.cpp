#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "biteopt.h"
#include <functional>
#include <vector>
#include <string>
extern "C" {

static PyObject* minimize_func(PyObject* self, PyObject* args, PyObject *kwargs)
{
    std::vector<double> upper, lower;
    PyObject * func_py = NULL;
    PyObject * upper_py = NULL;
    PyObject * lower_py = NULL;
    int iter_py = 1;
    int M_py = 1;
    int attc_py = 10;
    static const char *kwlist[] = {"func", "lower", "upper", "iter", "Mi", "attc", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OOO|iii", const_cast<char**>(kwlist), 
                                     &func_py, &lower_py, &upper_py, &iter_py, &M_py, &attc_py)) 
    {
        return NULL;
    }


    PyObject *iter = PyObject_GetIter(lower_py);
    if (!iter) {
        PyErr_SetString(PyExc_TypeError, "minimize: a list is required in 2nd pos");
        return 0;
    }

    while (true) {
        PyObject *next = PyIter_Next(iter);
        if (!next)
            break;

        lower.push_back(PyFloat_AsDouble(next));
        if(PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "minimize: numerical list is required");
            return 0;
        }
    }

    iter = PyObject_GetIter(upper_py);
    if (!iter) {
        PyErr_SetString(PyExc_TypeError, "minimize: a list is required in 3rd pos");
        return 0;
    }

    while (true) {
        PyObject *next = PyIter_Next(iter);
        if (!next)
            break;

        upper.push_back(PyFloat_AsDouble(next));
        if(PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "minimize: numerical list is required");
            return 0;
        }
    }

    if(lower.size() != upper.size()) {
        PyErr_SetString(PyExc_TypeError, "minimize: matching list lengths required");
        return 0;
    }
    for(size_t i=0; i < lower.size(); i++){
        if(lower[i] > upper[i]){
            PyErr_SetString(PyExc_TypeError, "minimize: lower should not be greater than upper");
            return 0;
        }
    }
    std::vector<double> best_x(lower.size());
    double min_f;

   


    struct FuncData {
        PyObject* func;
    };

    auto closure = [](int N, const double* x, void* func_data ) {
        auto list = PyList_New(0);
        for(auto i=0; i < N; ++i){
            PyList_Append(list, PyFloat_FromDouble(x[i]));
        }

       auto func_f = static_cast<FuncData*>(func_data);
       return PyFloat_AsDouble( PyObject_CallFunctionObjArgs(func_f->func, list,NULL));
    };

    FuncData fdata = {func_py}; // maybe add pass-thru args later
    biteopt_minimize( lower.size(), closure, (void*)&fdata, lower.data(), upper.data(), best_x.data(), &min_f, iter_py,M_py,attc_py );

    auto res = PyList_New(0);
    for(auto i: best_x) {
         PyList_Append(res, PyFloat_FromDouble(i));
    }
    return res ;
}

/*  define functions in module */
static PyMethodDef BiteOptMethods[] =
{
     {"minimize",(PyCFunction) minimize_func,  METH_VARARGS | METH_KEYWORDS, "func lower_bound (list) upper_bound (list) iter (int) M (int) attc (int)"},
     {NULL, NULL, 0, NULL}
};

#if PY_MAJOR_VERSION >= 3
/* module initialization */
/* Python version 3*/
static struct PyModuleDef cModPyDem =
{
    PyModuleDef_HEAD_INIT,
    "minimize", "Some minimization",
    -1,
    BiteOptMethods
};

PyMODINIT_FUNC
PyInit_biteopt(void)
{
    return PyModule_Create(&cModPyDem);
}

#else

/* module initialization */
/* Python version 2 */
PyMODINIT_FUNC
initbiteopt(void)
{
    (void) Py_InitModule("biteopt_module", BiteOptMethods);
}

#endif
}