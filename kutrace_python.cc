#define PY_SSIZE_T_CLEAN
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <Python.h>
#include "kutrace_lib/kutrace_lib.h"

// TODO (next): Delete almost this entire file and wrap all of the functions
// provided by kutrace_lib.h. Don't forget to add the kutrace source during
// compilation.

static PyObject* TestKUTrace(PyObject *self, PyObject *args) {
  bool ok = kutrace::test();
  if (ok) {
    Py_INCREF(Py_True);
    return Py_True;
  }
  Py_INCREF(Py_False);
  return Py_False;
}

static PyObject* Go(PyObject *self, PyObject *args) {
  const char *process_name = NULL;
  if (!PyArg_ParseTuple(args, "s", &process_name)) return NULL;
  kutrace::go(process_name);
  Py_RETURN_NONE;
}

static PyObject* GoIPC(PyObject *self, PyObject *args) {
  const char *process_name = NULL;
  if (!PyArg_ParseTuple(args, "s", &process_name)) return NULL;
  kutrace::goipc(process_name);
  Py_RETURN_NONE;
}

static PyObject* Stop(PyObject *self, PyObject *args) {
  const char *file_name = NULL;
  if (!PyArg_ParseTuple(args, "s", &file_name)) return NULL;
  kutrace::stop(file_name);
  Py_RETURN_NONE;
}

static PyObject* MarkA(PyObject *self, PyObject *args) {
  const char *label = NULL;
  if (!PyArg_ParseTuple(args, "s", &label)) return NULL;
  kutrace::mark_a(label);
  Py_RETURN_NONE;
}

static PyObject* MarkB(PyObject *self, PyObject *args) {
  const char *label = NULL;
  if (!PyArg_ParseTuple(args, "s", &label)) return NULL;
  kutrace::mark_b(label);
  Py_RETURN_NONE;
}

static PyObject* MarkC(PyObject *self, PyObject *args) {
  const char *label = NULL;
  if (!PyArg_ParseTuple(args, "s", &label)) return NULL;
  kutrace::mark_c(label);
  Py_RETURN_NONE;
}

static PyObject* MarkD(PyObject *self, PyObject *args) {
  unsigned long n;
  if (!PyArg_ParseTuple(args, "k", &n)) return NULL;
  kutrace::mark_d(n);
  Py_RETURN_NONE;
}

static PyObject* AddEvent(PyObject *self, PyObject *args) {
  unsigned long event_num, arg, result;
  if (!PyArg_ParseTuple(args, "kk", &event_num, &arg)) return NULL;
  result = kutrace::addevent(event_num, arg);
  return Py_BuildValue("k", result);
}

static PyObject* AddName(PyObject *self, PyObject *args) {
  unsigned long event_num, number;
  const char *name = NULL;
  if (!PyArg_ParseTuple(args, "kks", &event_num, &number, &name)) return NULL;
  kutrace::addname(event_num, number, name);
  Py_RETURN_NONE;
}

static PyObject* MSleep(PyObject *self, PyObject *args) {
  int msec;
  if (!PyArg_ParseTuple(args, "i", &msec)) return NULL;
  kutrace::msleep(msec);
  Py_RETURN_NONE;
}

static PyObject* ReadTime(PyObject *self, PyObject *args) {
  long int result = kutrace::readtime();
  return Py_BuildValue("l", result);
}

static PyMethodDef kutrace_methods[] = {
  {
    "test",
    TestKUTrace,
    METH_NOARGS,
    "Returns true if the module is loaded and OK. Otherwise returns false.",
  },
  {
    "go",
    Go,
    METH_VARARGS,
    "Starts tracing, without IPC. Requires one string arg: the process name.",
  },
  {
    "goipc",
    GoIPC,
    METH_VARARGS,
    "The same as \"go,\" but measures IPC as well.",
  },
  {
    "stop",
    Stop,
    METH_VARARGS,
    "Stops tracing, and writes the trace to a file. Requires one arg: the "
      "filename to write the trace to.",
  },
  {
    "mark_a",
    MarkA,
    METH_VARARGS,
    "Adds a label with an up to 6 character string to the trace. The label "
      "may only contain letters, numbers, ., /, and -.",
  },
  {
    "mark_b",
    MarkB,
    METH_VARARGS,
    "The same as mark_a, but with a different label appearance.",
  },
  {
    "mark_c",
    MarkC,
    METH_VARARGS,
    "The same as mark_a and mark_b, but with a different label appearance.",
  },
  {
    "mark_d",
    MarkD,
    METH_VARARGS,
    "Like mark_a, but marks with a single number rather than a string.",
  },
  {
    "addevent",
    AddEvent,
    METH_VARARGS,
    "Adds an arbitrary KUTrace event. Requires two args: the event number and "
      "an unsigned integer argument. Returns the number of words inserted, 0 "
      "if tracing is off, or negative if the KUtrace module is not loaded.",
  },
  {
    "addname",
    AddName,
    METH_VARARGS,
    "Adds the name of an event to the trace. Requires 3 args: the event "
       "number, the event's value, and the name string.",
  },
  {
    "msleep",
    MSleep,
    METH_VARARGS,
    "Takes one arg, a number of milliseconds, and sleeps for that duration.",
  },
  {
    "readtime",
    ReadTime,
    METH_NOARGS,
    "Returns a platform-specific perf counter value. See ku_get_cycles in "
      "kutrace_lib.cc.",
  },
  {NULL, NULL, 0, NULL},
};

static struct PyModuleDef kutrace_module = {
  PyModuleDef_HEAD_INIT,
  "kutrace",
  "A python wrapper around the KUtrace userspace API.",
  -1,
  kutrace_methods,
  NULL,
  NULL,
  NULL,
  NULL,
};

PyMODINIT_FUNC PyInit_kutrace(void) {
  return PyModule_Create(&kutrace_module);
}

