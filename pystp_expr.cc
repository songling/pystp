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
#include "pystp_expr.h"
#include "pystp_type.h"
#include "pystp_common.h"

extern PyTypeObject StpType_type;	/* StpType type object */

/* ========================================================================== *
 * <method> StpType getType()                                                 *
 * ========================================================================== */
PyObject* StpExpression_getType(StpExpression* self)
{
  Type type;

  type = vc_getType(self->stp_stp->solver, self->expr);

  /* now we must allocate a new StpType object */
  return (PyObject*) create_StpType_noref(self->stp_stp, type);
}

/* ========================================================================== *
 * <method> String __str__()                                                  *
 * ========================================================================== */
PyObject* StpExpression_str(PyObject* self)
{
  const char *s;
  PyObject *pystr;

  s = exprString(((StpExpression*)self)->expr);
  strrighttrim((char*)s);

  pystr = PyString_FromString(s);
  free((void*)s);

  return pystr;
}

/* ========================================================================== *
 * <method> int getBVInt()                                                    *
 * ========================================================================== */
PyObject* StpExpression_getBVInt(PyObject *self)
{
  return PyInt_FromLong(getBVInt(((StpExpression*)self)->expr));
}

/* ========================================================================== *
 * <method> unsigned int getBVUnsigned()                                      *
 * ========================================================================== */
PyObject* StpExpression_getBVUnsigned(PyObject *self)
{
  return PyInt_FromLong(getBVUnsigned(((StpExpression*)self)->expr));
}

/* ========================================================================== *
 * <method> unsigned long long int getBVUnsignedLongLong()                    *
 * ========================================================================== */
PyObject* StpExpression_getBVUnsignedLongLong(PyObject *self)
{
  return PyLong_FromLong(getBVUnsignedLongLong(((StpExpression*)self)->expr));
}

void StpExpression_dealloc(StpExpression* self)
{
  DEBUG(" * deallocating EXPR %p [linked to Stp@%p];\n", self->expr, self->stp_stp->solver);
  /* decrement reference */
  Py_DECREF(self->stp_stp);

  /* do actual deallocation */
  self->ob_type->tp_free((PyObject*)self);
}

PyObject* StpExpression_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  /* this class cannot be instantiated directly, but is created only by an Stp object */
  return NULL;
}

int StpExpression_init(StpExpression* self, PyObject *args, PyObject *kwds)
{
  return 0;
}
