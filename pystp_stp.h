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

#ifndef _PYSTP_STP_H
#define _PYSTP_STP_H

#include <Python.h>
#include "c_interface.h"
#include "pystp_list.h"

#define NELEMS_DEFAULT  32	/* default size for collection objects */

typedef struct {
  PyObject_HEAD

  VC solver;			/* actual STP object */

  tpystp_node *types_list;	/* list of associated StpType objects */
  tpystp_node *exps_list;	/* list of associated StpExpression objects */
} Stp;

/* --- Type generation methods --- */
PyObject* Stp_createType(Stp*, PyObject*);

/* --- Expr manipulation methods --- */
PyObject* Stp_varExpr(Stp*, PyObject*);
PyObject* Stp_varExpr1(Stp*, PyObject*);
PyObject* Stp_eqExpr(Stp*, PyObject*);

/* boolean expressions */
PyObject* Stp_trueExpr(Stp*);
PyObject* Stp_falseExpr(Stp*);
PyObject* Stp_notExpr(Stp*, PyObject*);
PyObject* Stp_andExpr(Stp*, PyObject*);
PyObject* Stp_orExpr(Stp*, PyObject*);
PyObject* Stp_impliesExpr(Stp*, PyObject*);
PyObject* Stp_iffExpr(Stp*, PyObject*);
PyObject* Stp_iteExpr(Stp*, PyObject*);

PyObject* Stp_readExpr(Stp*, PyObject*);
PyObject* Stp_writeExpr(Stp*, PyObject*);

PyObject* Stp_printCounterExample(Stp*);
PyObject* Stp_printVarDecls(Stp*);
PyObject* Stp_printAsserts(Stp*);
PyObject* Stp_getQueryState(Stp*, PyObject*);

/* --- bit vector operations --- */
PyObject* Stp_bvConstExprFromStr(Stp*, PyObject*);
PyObject* Stp_bvConstExprFromInt(Stp*, PyObject*);
PyObject* Stp_bvConstExprFromLL(Stp*, PyObject*);
PyObject* Stp_bv32ConstExprFromInt(Stp*, PyObject*);

PyObject* Stp_bvConcatExpr(Stp*, PyObject*);
PyObject* Stp_bvPlusExpr(Stp*, PyObject*);
PyObject* Stp_bv32PlusExpr(Stp*, PyObject*);
PyObject* Stp_bvMinusExpr(Stp*, PyObject*);
PyObject* Stp_bv32MinusExpr(Stp*, PyObject*);
PyObject* Stp_bvMultExpr(Stp*, PyObject*);
PyObject* Stp_bv32MultExpr(Stp*, PyObject*);
PyObject* Stp_bvDivExpr(Stp*, PyObject*);

PyObject* Stp_bvLtExpr(Stp*, PyObject*);
PyObject* Stp_bvLeExpr(Stp*, PyObject*);
PyObject* Stp_bvGtExpr(Stp*, PyObject*);
PyObject* Stp_bvGeExpr(Stp*, PyObject*);

PyObject* Stp_sbvLtExpr(Stp*, PyObject*);
PyObject* Stp_sbvLeExpr(Stp*, PyObject*);
PyObject* Stp_sbvGtExpr(Stp*, PyObject*);
PyObject* Stp_sbvGeExpr(Stp*, PyObject*);

PyObject* Stp_bvUMinusExpr(Stp*, PyObject*);

PyObject* Stp_bvAndExpr(Stp*, PyObject*);
PyObject* Stp_bvOrExpr(Stp*, PyObject*);
PyObject* Stp_bvXorExpr(Stp*, PyObject*);
PyObject* Stp_bvNotExpr(Stp*, PyObject*);

PyObject* Stp_bvLeftShiftExpr(Stp*, PyObject*);
PyObject* Stp_bvRightShiftExpr(Stp*, PyObject*);

PyObject* Stp_bvExtract(Stp*, PyObject*);
PyObject* Stp_bvBoolExtract(Stp*, PyObject*);
PyObject* Stp_bvSignExtend(Stp*, PyObject*);

PyObject* Stp_bvCreateMemoryArray(Stp*, PyObject*);
PyObject* Stp_bvReadMemoryArray(Stp*, PyObject*);
PyObject* Stp_bvWriteToMemoryArray(Stp*, PyObject*);

/* --- context-related methods --- */
PyObject* Stp_assertFormula(Stp*, PyObject*);
PyObject* Stp_simplify(Stp*, PyObject*);
PyObject* Stp_query(Stp*, PyObject*);
PyObject* Stp_getCounterExample(Stp*, PyObject*);
PyObject* Stp_counterExample_size(Stp*);
PyObject* Stp_push(Stp*);
PyObject* Stp_pop(Stp*);
PyObject* Stp_setFlags(Stp*, PyObject*);

PyObject* Stp_deleteExpr(Stp*, PyObject*);
PyObject* Stp_destroy(Stp*);

void Stp_dealloc(Stp*);
int  Stp_init(Stp*, PyObject*, PyObject*);

#endif /* _PYSTP_STP_H */
