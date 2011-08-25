/*
  Copyright notice
  ================

  Copyright (C)
      Lorenzo  Martignoni <martignlo@gmail.com>
      Roberto  Paleari    <roberto.paleari@gmail.com>

  This program is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation; either version 2 of the License, or (at your option) any later
  version.  

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

static const char id[] = "$Id$";

#ifdef __cplusplus
extern "C" {
#endif
#include <Python.h>
#include <structmember.h>
#ifdef __cplusplus
}
#endif

#include "c_interface.h"

#include "pystp_common.h"
#include "pystp.h"		/* PythonType definitions */
#include "pystp_stp.h"		/* Stp object */
#include "pystp_expr.h"		/* StpExpression object */
#include "pystp_type.h"		/* StpType object */

/* === pystp methods === */

static PyMemberDef pystp_members[] = {
  {NULL}   /* Sentinel */
};

static PyMethodDef pystp_methods[] = {
  {"setFlags", (PyCFunction)PyStp_setFlags, METH_VARARGS,
   "setFlags(flags) -> None\n"
   "Set the specified constraints solver flags ('flags' must be a string)."},
  {NULL}   /* Sentinel */
};

#ifndef PyMODINIT_FUNC   /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif

static PyObject* PyStp_setFlags(PyObject *self, PyObject *args)
{
  char *flags;
  char c;
  int i;

  flags = NULL;
  if(!PyArg_ParseTuple(args, "s", &flags))
    /* error parsing input parameters */
    return NULL;

  for(i=0; i<strlen(flags); i++) {
    c = flags[i];
    /* check flag validity */
    if(c != 'r' && c != 'w' && c != 'a' && c != 's' &&
       c != 'v' && c != 'c' && c != 'd' && c != 'p' &&
       c != 'h' && c != 'n' && c != 'x') {
      /* flag is NOT valid. Skip it */ 
      DEBUG("warning: skipping invalid flag '%c';\n", c);
      continue;
    }

    vc_setFlags(c);
  }

  Py_INCREF(Py_None);
  return Py_None;
}

#ifdef __cplusplus
extern "C" 
#endif
void initpystp(void)
{
  PyObject* m;

  if (PyType_Ready(&Stp_type) < 0 || PyType_Ready(&StpExpression_type) < 0 ||
      PyType_Ready(&StpType_type) < 0)
    return;

  m = Py_InitModule3("pystp", pystp_methods, "STP constraint solver.");
  
  Py_INCREF(&Stp_type);
  PyModule_AddObject(m, "Stp", (PyObject*)&Stp_type);

  Py_INCREF(&StpExpression_type);
  PyModule_AddObject(m, "StpExpression", (PyObject*)&StpExpression_type);

  Py_INCREF(&StpType_type);
  PyModule_AddObject(m, "StpType", (PyObject*)&StpType_type);

  /* add some constants */

  /* types */
  PyModule_AddIntConstant(m, "TYPE_BOOL",      0);
  PyModule_AddIntConstant(m, "TYPE_ARRAY",     1);
  PyModule_AddIntConstant(m, "TYPE_BITVECTOR", 2);

  /* expressions */
  PyModule_AddIntConstant(m, "EXPR_VARIABLE", 0);
  PyModule_AddIntConstant(m, "EXPR_EQUAL",    1);
  PyModule_AddIntConstant(m, "EXPR_TRUE",     2);
  PyModule_AddIntConstant(m, "EXPR_FALSE",    3);
  PyModule_AddIntConstant(m, "EXPR_NOT",      4);
  PyModule_AddIntConstant(m, "EXPR_AND",      5);
  PyModule_AddIntConstant(m, "EXPR_OR",       6);
  PyModule_AddIntConstant(m, "EXPR_IMPLIES",  7);
  PyModule_AddIntConstant(m, "EXPR_IFF",      8);
  PyModule_AddIntConstant(m, "EXPR_ITE",      9);
}
