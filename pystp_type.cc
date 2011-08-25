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

#include <Python.h>
#include "pystp_type.h"
#include "pystp_common.h"

PyObject* StpType_isBool(StpType *self)
{
  CHECKTYPE(self, "BOOLEAN")
}

PyObject* StpType_isBitVector(StpType *self)
{
  CHECKTYPE(self, "BITVECTOR")
}

PyObject* StpType_isArray(StpType *self)
{
  CHECKTYPE(self, "ARRAY")
}

PyObject* StpType_str(PyObject* self)
{
  const char *s;
  PyObject *pystr;

  s = typeString(((StpType*)self)->type);

  strrighttrim((char*)s);

  pystr = PyString_FromString(s);
  free((void*)s);

  return pystr;
}

void StpType_dealloc(StpType* self)
{
  DEBUG(" * deallocating TYPE %p [linked to Stp@%p];\n", self->type, self->stp_stp->solver);
  /* decrement references */
  Py_DECREF(self->stp_stp);

  /* do actual deallocation */
  self->ob_type->tp_free((PyObject*)self);
}

PyObject* StpType_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  /* this class cannot be instantiated directly, but is created only by an Stp object */
  return NULL;
}

int StpType_init(StpType* self, PyObject *args, PyObject *kwds)
{
  return 0;
}
