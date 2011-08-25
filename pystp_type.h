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

#ifndef _PYSTP_TYPE_H
#define _PYSTP_TYPE_H

#include <Python.h>
#include "pystp_stp.h"
#include "c_interface.h"

#define CHECKTYPE(pstp_type, type_string)                  \
{                                                          \
  const char *s;                                           \
  int retval;                                              \
                                                           \
  s = typeString(pstp_type->type);                         \
  retval = strncmp(s, type_string, strlen(type_string));   \
  free((void*) s);                                         \
                                                           \
  if(!retval)                                              \
    Py_RETURN_TRUE;                                        \
  else                                                     \
    Py_RETURN_FALSE;                                       \
}

typedef struct {
  PyObject_HEAD

  Type type;			/* actual STP Type object associated to this StpType instance */

  Stp*  stp_stp;		/* the associated Stp object */  
} StpType;

PyObject* StpType_isBool(StpType*);
PyObject* StpType_isBitVector(StpType*);
PyObject* StpType_isArray(StpType*);

PyObject* StpType_str(PyObject*);

void StpType_dealloc(StpType*);
PyObject* StpType_new(PyTypeObject*, PyObject*, PyObject*);
int StpType_init(StpType*, PyObject*, PyObject*);

#endif /* _PYSTP_TYPE_H */
