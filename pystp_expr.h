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

#ifndef _PYSTP_EXPR_H
#define _PYSTP_EXPR_H

#include <Python.h>
#include "pystp_stp.h"
#include "pystp_type.h"
#include "c_interface.h"

typedef struct {
  PyObject_HEAD

  Expr expr;			/* the STP expression object */

  Stp*  stp_stp;		/* the associated Stp object */
} StpExpression;

PyObject* StpExpression_getType(StpExpression*);
PyObject* StpExpression_str(PyObject*);
PyObject* StpExpression_getBVInt(PyObject*);
PyObject* StpExpression_getBVUnsigned(PyObject*);
PyObject* StpExpression_getBVUnsignedLongLong(PyObject*);

void StpExpression_dealloc(StpExpression*);
PyObject* StpExpression_new(PyTypeObject*, PyObject*, PyObject*);
int StpExpression_init(StpExpression*, PyObject*, PyObject*);

#endif /* _PYSTP_EXPR_H */
