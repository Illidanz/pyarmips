
#include "Core/Assembler.h"

extern "C"
{
    #include <Python.h>

    static PyObject *method_run(PyObject *self, PyObject *args, PyObject *kwargs)
    {
        char *filename = NULL;
        char *tempFilename = NULL;
        char *symFilename = NULL;
        int symFileVersion = 0;
        int useAbsoluteFilenames = 1;
        int errorOnWarning = 0;
        int silent = 0;
        int showStats = 0;

        static char *kwlist[] = {"filename", "tempFilename", "symFilename", "symFileVersion",
                                 "useAbsoluteFilenames", "errorOnWarning", "silent", "showStats",
                                 NULL};

        if(!PyArg_ParseTupleAndKeywords(args, kwargs, "s|ssIpppp", kwlist,
                                        &filename, &tempFilename, &symFilename, &symFileVersion,
                                        &useAbsoluteFilenames, &errorOnWarning, &silent, &showStats))
            return NULL;

        ArmipsArguments arguments;
        arguments.mode = ArmipsMode::FILE;
        arguments.inputFileName = filename;
        arguments.tempFileName = tempFilename == NULL ? "" : tempFilename;
        arguments.symFileName = symFilename == NULL ? "" : symFilename;
        arguments.symFileVersion = symFileVersion;
        arguments.useAbsoluteFileNames = useAbsoluteFilenames == 1;
        arguments.errorOnWarning = errorOnWarning == 1;
        arguments.silent = silent == 1;
        arguments.showStats = showStats == 1;
        bool result = runArmips(arguments);
        return PyBool_FromLong((long)result);
    }

    static PyMethodDef PyarmipsMethods[] = {
        {"run", (PyCFunction)method_run, METH_VARARGS | METH_KEYWORDS, "Python interface for armips."},
        {NULL, NULL, 0, NULL}
    };

    static struct PyModuleDef pyarmipsmodule = {
        PyModuleDef_HEAD_INIT,
        "pyarmips",
        "Python interface for armips.",
        -1,
        PyarmipsMethods
    };

    PyMODINIT_FUNC PyInit_pyarmips(void)
    {
        return PyModule_Create(&pyarmipsmodule);
    }
}
