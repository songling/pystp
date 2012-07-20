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
#include <assert.h>
#include "c_interface.h"
#include "pystp_stp.h"
#include "pystp_common.h"
#include "pystp_list.h"
#include "pystp_type.h"
#include "pystp_expr.h"

extern PyTypeObject Stp_type;
extern PyTypeObject StpType_type;
extern PyTypeObject StpExpression_type;

typedef Expr (*pair1_handler)(VC, Expr);
typedef Expr (*pair2_handler)(VC, Expr, Expr);

/* this helper function returns a StpExpr object obtained by invoking an
   STP function (specified thorugh the function pointer) over a single StpExpr 
   object */
static PyObject* pair1Expression(Stp *self, PyObject *args, pair1_handler f)
{
  StpExpression *pstpexpr;
  Expr expr;

  if(!PyArg_ParseTuple(args, "O!", 
		       &StpExpression_type, &pstpexpr))
    /* error parsing input parameters */
    return NULL;

  expr = f(self->solver, pstpexpr->expr);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* this helper function returns a StpExpr object obtained by combining together
   two other StpExpr objects with the given handler function */
static PyObject* pair2Expressions(Stp *self, PyObject *args, pair2_handler f)
{
  StpExpression *pstpexpr_left, *pstpexpr_right;
  Expr expr;

  if(!PyArg_ParseTuple(args, "O!O!", 
		       &StpExpression_type, &pstpexpr_left,
		       &StpExpression_type, &pstpexpr_right))
    /* error parsing input parameters */
    return NULL;

  expr = f(self->solver, pstpexpr_left->expr, pstpexpr_right->expr);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpr impliesExpr(hyp, conc)                                    *
 * ========================================================================== */
PyObject* Stp_impliesExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_impliesExpr);
}

/* ========================================================================== *
 * <method> StpExpr iffExpr(left, right)                                      *
 * ========================================================================== */
PyObject* Stp_iffExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_iffExpr);
}

/* ========================================================================== *
 * <method> StpExpression  iteExpr(conditional, ifthenpart, elsepart)         *
 * ========================================================================== */
PyObject* Stp_iteExpr(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr_cond, *pstpexpr_if, *pstpexpr_else; 
  Expr e;

  if(!PyArg_ParseTuple(args, "O!O!O!",
		       &StpExpression_type, &pstpexpr_cond,
		       &StpExpression_type, &pstpexpr_if,
		       &StpExpression_type, &pstpexpr_else
		       )
     )
    /* error parsing input parameters */
    return NULL;

  e = vc_iteExpr(self->solver, pstpexpr_cond->expr, 
		 pstpexpr_if->expr, pstpexpr_else->expr);

  /* allocate a new StpExpression object that represents this expression */
  return (PyObject*) create_StpExpr(self, e);
}

/* ========================================================================== *
 * <method> StpExpression  readExpr(array, index)                             *
 * ========================================================================== */
PyObject* Stp_readExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_readExpr);
}

/* ========================================================================== *
 * <method> StpExpression  writeExpr(array, index, newValue)                  *
 * ========================================================================== */
PyObject* Stp_writeExpr(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr_array, *pstpexpr_index, 
    *pstpexpr_new;
  Expr e;

  if(!PyArg_ParseTuple(args, "O!O!O!",
		       &StpExpression_type, &pstpexpr_array,
		       &StpExpression_type, &pstpexpr_index,
		       &StpExpression_type, &pstpexpr_new
		       )
     )
    /* error parsing input parameters */
    return NULL;

  e = vc_writeExpr(self->solver, pstpexpr_array->expr, 
		   pstpexpr_index->expr, pstpexpr_new->expr);

  /* allocate a new StpExpression object that represents this expression */
  return (PyObject*) create_StpExpr(self, e);
}

/* ========================================================================== *
 * <method> void  printCounterExample()                                       *
 * ========================================================================== */
PyObject* Stp_printCounterExample(Stp *self)
{
  vc_printCounterExample(self->solver);

  Py_INCREF(Py_None);
  return Py_None;
}

/* ========================================================================== *
 * <method> void  printVarDecls()                                             *
 * ========================================================================== */
PyObject* Stp_printVarDecls(Stp *self)
{
  vc_printVarDecls(self->solver);

  Py_INCREF(Py_None);
  return Py_None;
}

/* ========================================================================== *
 * <method> void  printAsserts()                                              *
 * ========================================================================== */
PyObject* Stp_printAsserts(Stp *self)
{
  vc_printAsserts(self->solver);

  Py_INCREF(Py_None);
  return Py_None;
}

/* ========================================================================== *
 * <method> String getQueryState(e)                                           *
 * ========================================================================== */
PyObject* Stp_getQueryState(Stp *self, PyObject *args)
{
  char *buf;
  unsigned long len;
  PyObject *pystr;
  StpExpression *pstpexpr;

  if(!PyArg_ParseTuple(args, "O!",
		       &StpExpression_type, &pstpexpr
		       )
     )
    /* error parsing input parameters */
    return NULL;

  vc_printQueryStateToBuffer(self->solver, pstpexpr->expr, &buf, &len, 1);

  pystr = PyString_FromString(buf);

  free(buf);			/* can we free this buffer? */
  return pystr;
}

/* ========================================================================== *
 * <method> StpExpr andExpr([expr0, expr1, ..., exprN])                       *
 * ========================================================================== */
PyObject* Stp_andExpr(Stp* self, PyObject* args)
{
  PyListObject *pstp_exprs_list;
  PyObject *pobj;
  Expr* pexprs_list;
  Expr  expr_and;
  int i, nchildren;

  if(!PyArg_ParseTuple(args, "O!",
		       &PyList_Type, &pstp_exprs_list /* children list */
		       )
     )
    /* error parsing input parameters */
    return NULL;

  nchildren = PyList_Size((PyObject*)pstp_exprs_list);

  if(nchildren < 2)
    /* invalid length. We need at least 2 expressions to join together */
    return NULL;

  /* type checking, in order to be sure that every element of our list
     is an instance of the StpExpr class */
  for(i=0; i<nchildren; i++) {
    pobj = PyList_GetItem((PyObject*)pstp_exprs_list, i);
    assert(pobj != NULL);	/* this should never happen */

    if(!PyObject_IsInstance(pobj, (PyObject*)&StpExpression_type))
      /* wrong instance */
      return NULL;
  }

  /* build an array of Expr objects */
  pexprs_list = (Expr*) malloc(nchildren * sizeof(Expr));
  if(!pexprs_list)
    /* dynamic allocation error */
    return PyErr_SetFromErrno(PyExc_OSError);
  for(i=0; i<nchildren; i++) {
    pobj = PyList_GetItem((PyObject*)pstp_exprs_list, i);
    pexprs_list[i] = ((StpExpression*)pobj)->expr;
  }

  /* create the new 'and' expression */
  expr_and = vc_andExprN(self->solver, pexprs_list, nchildren);

  /* allocate a new StpExpression object that represents this expression */
  return (PyObject*) create_StpExpr(self, expr_and);
}

/* ========================================================================== *
 * <method> StpExpr orExpr([expr0, expr1, ..., exprN])                       *
 * ========================================================================== */
PyObject* Stp_orExpr(Stp* self, PyObject* args)
{
  PyListObject *pstp_exprs_list;
  PyObject *pobj;
  Expr* pexprs_list;
  Expr  expr_or;
  int i, nchildren;

  if(!PyArg_ParseTuple(args, "O!",
		       &PyList_Type, &pstp_exprs_list /* children list */
		       )
     ) {
    /* error parsing input parameters */
    return NULL;
  }

  nchildren = PyList_Size((PyObject*)pstp_exprs_list);

  if(nchildren < 2)
    /* invalid length. We need at least 2 expressions to join together */
    return NULL;

  /* type checking, in order to be sure that every element of our list
     is an instance of the StpExpr class */
  for(i=0; i<nchildren; i++) {
    pobj = PyList_GetItem((PyObject*)pstp_exprs_list, i);
    assert(pobj != NULL);	/* this should never happen */

    if(!PyObject_IsInstance(pobj, (PyObject*)&StpExpression_type))
      /* wrong instance */
      return NULL;
  }

  /* build an array of Expr objects */
  pexprs_list = (Expr*) malloc(nchildren * sizeof(Expr));
  if(!pexprs_list)
    /* dynamic allocation error */
    return PyErr_SetFromErrno(PyExc_OSError);
  for(i=0; i<nchildren; i++) {
    pobj = PyList_GetItem((PyObject*)pstp_exprs_list, i);
    pexprs_list[i] = ((StpExpression*)pobj)->expr;
  }

  /* create the new 'or' expression */
  expr_or = vc_orExprN(self->solver, pexprs_list, nchildren);

  /* allocate a new StpExpression object that represents this expression */
  return (PyObject*) create_StpExpr(self, expr_or);
}


/* ========================================================================== *
 * <method> StpExpr notExpr(expr)                                             *
 * ========================================================================== */
PyObject* Stp_notExpr(Stp* self, PyObject* args)
{
  return pair1Expression(self, args, vc_notExpr);
}

/* ========================================================================== *
 * <method> StpExpr trueExpr()                                                *
 * ========================================================================== */
PyObject* Stp_trueExpr(Stp* self)
{
  Expr e;

  e = vc_trueExpr(self->solver);
  return (PyObject*) create_StpExpr(self, e);
}

/* ========================================================================== *
 * <method> StpExpr falseExpr()                                               *
 * ========================================================================== */
PyObject* Stp_falseExpr(Stp* self)
{
  Expr e;

  e = vc_falseExpr(self->solver);
  return (PyObject*) create_StpExpr(self, e);
}

/* ========================================================================== *
 * <method> StpExpr eqExpr(child0, child1)                                    *
 * ========================================================================== */
PyObject* Stp_eqExpr(Stp* self, PyObject* args)
{
  return pair2Expressions(self, args, vc_eqExpr);
}

/* ========================================================================== *
 * <method> StpExpr varExpr(name, type)                                       *
 * ========================================================================== */
PyObject* Stp_varExpr(Stp* self, PyObject* args)
{
  char* name;
  StpType* stp_type;
  Expr expr;

  if(!PyArg_ParseTuple(args, "sO!", 
		       &name,	/* variable name */
		       &StpType_type,
		       &stp_type
		       )
     ) {
    /* error parsing input parameters */
    return NULL;
  }

  /* create the 'Expr' object */
  expr = vc_varExpr(self->solver, name, stp_type->type);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpr varExpr1(name, indexwidth, valuewidth)                    *
 * ========================================================================== */
PyObject* Stp_varExpr1(Stp* self, PyObject* args)
{
  char* name;
  int indexwidth, valuewidth;
  Expr expr;

  if(!PyArg_ParseTuple(args, "sii", 
		       &name,	/* variable name */
		       &indexwidth,
		       &valuewidth
		       )
     ) {
    /* error parsing input parameters */
    return NULL;
  }

  /* create the 'Expr' object */
  expr = vc_varExpr1(self->solver, name, indexwidth, valuewidth);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ==================================================================== */
/* === TYPE GENERATION METHODS ======================================== */
/* ==================================================================== */

/* ========================================================================== *
 * <method> StpType createType(type [, nelems])                               *
 * ========================================================================== */
PyObject* Stp_createType(Stp* self, PyObject *args)
{
  Type var_type;
  int itype, nelems;

  /* init optional arguments to their default value */
  nelems = 0;

  if(!PyArg_ParseTuple(args, "i|i", 
		       &itype, 	             /* Type type */
		       &nelems               /* number of elements in a collection */
		       )
     )
    /* error parsing input parameters */
    return NULL;

  /* check arguments */
  if(
     /* invalid Type type */
     (itype != TYPE_BOOL && itype != TYPE_ARRAY && itype != TYPE_BITVECTOR) ||
     /* number of elements in a collection */
     (itype != TYPE_BOOL && nelems < 0)
     ) {
    return NULL;
  }

  if(itype != TYPE_BOOL && nelems == 0) {
    /* collection Type with missing 'nelems'.. Set to default value */
    nelems = NELEMS_DEFAULT;
  }

  switch(itype) {
  case TYPE_BOOL:
    var_type = vc_boolType(self->solver);
    DEBUG("[Stp@%p] created Type: %s (%p);\n", self->solver, typeString(var_type), var_type)
    break;
  case TYPE_ARRAY:
    /* not implemented */
    return NULL;
    break;
  case TYPE_BITVECTOR:
    var_type = vc_bvType(self->solver, nelems);
    DEBUG("[Stp@%p] created Type: %s (%p);\n", self->solver, typeString(var_type), var_type)
    break;
  }

  /* now we must allocate a new StpType object */
  return (PyObject*) create_StpType(self, var_type);
}

/* ==================================================================== */
/* === BIT VECTOR OPERATIONS ========================================== */
/* ==================================================================== */

/* ========================================================================== *
 * <method> StpExpression bvConstExprFromStr(binary_repr)                     *
 * ========================================================================== */
PyObject* Stp_bvConstExprFromStr(Stp* self, PyObject *args)
{
  char *pbinary;
  Expr expr;

  if(!PyArg_ParseTuple(args, "s", &pbinary))
    /* error parsing input parameters */
    return NULL;  

  expr = vc_bvConstExprFromStr(self->solver, pbinary);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvConstExprFromInt(n_bits, value)                   *
 * ========================================================================== */
PyObject* Stp_bvConstExprFromInt(Stp* self, PyObject *args)
{
  int n_bits;
  unsigned int value;
  Expr expr;

  if(!PyArg_ParseTuple(args, "iI", &n_bits, &value))
    /* error parsing input parameters */
    return NULL;

  expr = vc_bvConstExprFromInt(self->solver, n_bits, value);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvConstExprFromLL(n_bits, value)                    *
 * ========================================================================== */
PyObject* Stp_bvConstExprFromLL(Stp* self, PyObject *args)
{
  int n_bits;
  unsigned long long value;
  Expr expr;

  if(!PyArg_ParseTuple(args, "iK", &n_bits, &value))
    /* error parsing input parameters */
    return NULL;

  expr = vc_bvConstExprFromLL(self->solver, n_bits, value);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bv32ConstExprFromInt(value)                         *
 * ========================================================================== */
PyObject* Stp_bv32ConstExprFromInt(Stp* self, PyObject *args)
{
  unsigned int value;
  Expr expr;

  if(!PyArg_ParseTuple(args, "I", &value))
    /* error parsing input parameters */
    return NULL;

  expr = vc_bv32ConstExprFromInt(self->solver, value);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvConcatExpr(left, right)                           *
 * ========================================================================== */
PyObject* Stp_bvConcatExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_bvConcatExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvPlusExpr(n_bits, left, right)                     *
 * ========================================================================== */
PyObject* Stp_bvPlusExpr(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr_left, *pstpexpr_right;
  int n_bits;
  Expr expr;

  if(!PyArg_ParseTuple(args, "iO!O!",
		       &n_bits,
		       &StpExpression_type, &pstpexpr_left,
		       &StpExpression_type, &pstpexpr_right))
    /* error parsing input parameters */
    return NULL;

  expr = vc_bvPlusExpr(self->solver, n_bits,
		       pstpexpr_left->expr, 
		       pstpexpr_right->expr);


  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bv32PlusExpr(left, right)                           *
 * ========================================================================== */
PyObject* Stp_bv32PlusExpr(Stp *self, PyObject *args)
{
    return pair2Expressions(self, args, vc_bv32PlusExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvMinusExpr(n_bits, left, right)                     *
 * ========================================================================== */
PyObject* Stp_bvMinusExpr(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr_left, *pstpexpr_right;
  int n_bits;
  Expr expr;

  if(!PyArg_ParseTuple(args, "iO!O!",
		       &n_bits,
		       &StpExpression_type, &pstpexpr_left,
		       &StpExpression_type, &pstpexpr_right))
    /* error parsing input parameters */
    return NULL;

  expr = vc_bvMinusExpr(self->solver, n_bits,
		       pstpexpr_left->expr, 
		       pstpexpr_right->expr);


  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bv32MinusExpr(left, right)                           *
 * ========================================================================== */
PyObject* Stp_bv32MinusExpr(Stp *self, PyObject *args)
{
    return pair2Expressions(self, args, vc_bv32MinusExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvMultExpr(n_bits, left, right)                     *
 * ========================================================================== */
PyObject* Stp_bvMultExpr(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr_left, *pstpexpr_right;
  int n_bits;
  Expr expr;

  if(!PyArg_ParseTuple(args, "iO!O!",
		       &n_bits,
		       &StpExpression_type, &pstpexpr_left,
		       &StpExpression_type, &pstpexpr_right))
    /* error parsing input parameters */
    return NULL;

  expr = vc_bvMultExpr(self->solver, n_bits,
		       pstpexpr_left->expr, 
		       pstpexpr_right->expr);


  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bv32MultExpr(left, right)                           *
 * ========================================================================== */
PyObject* Stp_bv32MultExpr(Stp *self, PyObject *args)
{
    return pair2Expressions(self, args, vc_bv32MultExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvDivExpr(n_bits, left, right)                     *
 * ========================================================================== */
PyObject* Stp_bvDivExpr(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr_left, *pstpexpr_right;
  int n_bits;
  Expr expr;

  if(!PyArg_ParseTuple(args, "iO!O!",
		       &n_bits,
		       &StpExpression_type, &pstpexpr_left,
		       &StpExpression_type, &pstpexpr_right))
    /* error parsing input parameters */
    return NULL;

  expr = vc_bvDivExpr(self->solver, n_bits,
		      pstpexpr_left->expr, 
		      pstpexpr_right->expr);


  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvLtExpr(left, right)                               *
 * ========================================================================== */
PyObject* Stp_bvLtExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_bvLtExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvLeExpr(left, right)                               *
 * ========================================================================== */
PyObject* Stp_bvLeExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_bvLeExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvGtExpr(left, right)                               *
 * ========================================================================== */
PyObject* Stp_bvGtExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_bvGtExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvGeExpr(left, right)                               *
 * ========================================================================== */
PyObject* Stp_bvGeExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_bvGeExpr);
}

/* ========================================================================== *
 * <method> StpExpression sbvLtExpr(left, right)                              *
 * ========================================================================== */
PyObject* Stp_sbvLtExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_sbvLtExpr);
}

/* ========================================================================== *
 * <method> StpExpression sbvLeExpr(left, right)                              *
 * ========================================================================== */
PyObject* Stp_sbvLeExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_sbvLeExpr);
}

/* ========================================================================== *
 * <method> StpExpression sbvGtExpr(left, right)                              *
 * ========================================================================== */
PyObject* Stp_sbvGtExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_sbvGtExpr);
}

/* ========================================================================== *
 * <method> StpExpression sbvGeExpr(left, right)                              *
 * ========================================================================== */
PyObject* Stp_sbvGeExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_sbvGeExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvUMinusExpr(child)                                 *
 * ========================================================================== */
PyObject* Stp_bvUMinusExpr(Stp *self, PyObject *args)
{
  return pair1Expression(self, args, vc_bvUMinusExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvAndExpr(left, right)                              *
 * ========================================================================== */
PyObject* Stp_bvAndExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_bvAndExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvOrExpr(left, right)                               *
 * ========================================================================== */
PyObject* Stp_bvOrExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_bvOrExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvXorExpr(left, right)                              *
 * ========================================================================== */
PyObject* Stp_bvXorExpr(Stp *self, PyObject *args)
{
  return pair2Expressions(self, args, vc_bvXorExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvNotExpr(child)                                    *
 * ========================================================================== */
PyObject* Stp_bvNotExpr(Stp *self, PyObject *args)
{
  return pair1Expression(self, args, vc_bvNotExpr);
}

/* ========================================================================== *
 * <method> StpExpression bvLeftShiftExpr(sh_amt, child)                      *
 * ========================================================================== */
PyObject* Stp_bvLeftShiftExpr(Stp *self, PyObject *args)
{
  StpExpression *pystpexpr_child;
  int sh_amt;
  Expr expr;

  if(!PyArg_ParseTuple(args, "iO!", 
		       &sh_amt,
		       &StpExpression_type, &pystpexpr_child
		       )
     ) {
    /* error parsing input parameters */
    return NULL;
  }

  expr = vc_bvLeftShiftExpr(self->solver, sh_amt, pystpexpr_child->expr);
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvRightShiftExpr(sh_amt, child)                     *
 * ========================================================================== */
PyObject* Stp_bvRightShiftExpr(Stp *self, PyObject *args)
{
  StpExpression *pystpexpr_child;
  int sh_amt;
  Expr expr;

  if(!PyArg_ParseTuple(args, "iO!", 
		       &sh_amt,
		       &StpExpression_type, &pystpexpr_child
		       )
     ) {
    /* error parsing input parameters */
    return NULL;
  }

  expr = vc_bvRightShiftExpr(self->solver, sh_amt, pystpexpr_child->expr);
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpr bvExtract(child, high_bit_no, low_bit_no)                 *
 * ========================================================================== */
PyObject* Stp_bvExtract(Stp* self, PyObject* args)
{
  int high_bit_no, low_bit_no;
  StpExpression *pystpexpr_in;
  Expr expr;

  if(!PyArg_ParseTuple(args, "O!ii", 
		       &StpExpression_type, &pystpexpr_in,
		       &high_bit_no,
		       &low_bit_no
		       )
     ) {
    /* error parsing input parameters */
    return NULL;
  }

  /* create the 'Expr' object */
  expr = vc_bvExtract(self->solver, pystpexpr_in->expr, 
		      high_bit_no, low_bit_no);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvBoolExtract(x, bit_no)                            *
 * ========================================================================== */
PyObject* Stp_bvBoolExtract(Stp *self, PyObject *args)
{
  int bit_no;
  StpExpression *pystpexpr;
  Expr expr;

  if(!PyArg_ParseTuple(args, "O!i", 
		       &StpExpression_type, &pystpexpr,
		       &bit_no
		       )
     ) {
    /* error parsing input parameters */
    return NULL;
  }

  expr = vc_bvBoolExtract(self->solver, pystpexpr->expr, bit_no);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvSignExtend(child, nbits)                          *
 * ========================================================================== */
PyObject* Stp_bvSignExtend(Stp *self, PyObject *args)
{
  int nbits;
  StpExpression *pystpexpr;
  Expr expr;

  if(!PyArg_ParseTuple(args, "O!i", 
		       &StpExpression_type, &pystpexpr,
		       &nbits
		       )
     ) {
    /* error parsing input parameters */
    return NULL;
  }

  expr = vc_bvSignExtend(self->solver, pystpexpr->expr, nbits);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvCreateMemoryArray(arrayName)                      *
 * ========================================================================== */
PyObject* Stp_bvCreateMemoryArray(Stp *self, PyObject *args)
{
  char *arrayName;
  StpExpression *pystpexpr;
  Expr expr;

  if(!PyArg_ParseTuple(args, "s", &arrayName))
    /* error parsing input parameters */
    return NULL;

  expr = vc_bvCreateMemoryArray(self->solver, arrayName);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr);
}

/* ========================================================================== *
 * <method> StpExpression bvReadMemoryArray(array, byteIndex, numOfBytes)     *
 * ========================================================================== */
PyObject* Stp_bvReadMemoryArray(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr_in, *pstpexpr_byteIndex;
  int numOfBytes;
  Expr expr_out;

  if(!PyArg_ParseTuple(args, "O!O!i",
		       &StpExpression_type, &pstpexpr_in,
		       &StpExpression_type, &pstpexpr_byteIndex,
		       &numOfBytes))
    /* error parsing input parameters */
    return NULL;

  expr_out = vc_bvReadMemoryArray(self->solver, 
				  pstpexpr_in->expr, 
				  pstpexpr_byteIndex->expr, 
				  numOfBytes);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr_out);
}

/* ========================================================================== *
 * <method> StpExpression bvWriteToMemoryArray(array, byteIndex, element, numOfBytes) *
 * ========================================================================== */
PyObject* Stp_bvWriteToMemoryArray(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr_in,
    *pstpexpr_byteIndex, *pstpexpr_element;
  int numOfBytes;
  Expr expr_out;

  if(!PyArg_ParseTuple(args, "O!O!O!i",
		       &StpExpression_type, &pstpexpr_in,
		       &StpExpression_type, &pstpexpr_byteIndex,
		       &StpExpression_type, &pstpexpr_element,
		       &numOfBytes))
    /* error parsing input parameters */
    return NULL;

  expr_out = vc_bvWriteToMemoryArray(self->solver, 
				     pstpexpr_in->expr, 
				     pstpexpr_byteIndex->expr,
				     pstpexpr_element->expr,
				     numOfBytes);

  /* now we must allocate a new StpExpression object */
  return (PyObject*) create_StpExpr(self, expr_out);
}

/* ==================================================================== */
/* === CONTEXT-RELATED METHODS ======================================== */
/* ==================================================================== */

/* ========================================================================== *
 * <method> void assertFormula(e)                                             *
 * ========================================================================== */
PyObject* Stp_assertFormula(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr;

  if(!PyArg_ParseTuple(args, "O!", &StpExpression_type, &pstpexpr))
    /* error parsing input parameters */
    return NULL;

  vc_assertFormula(self->solver, pstpexpr->expr);

  Py_INCREF(Py_None);
  return Py_None;
}

/* ========================================================================== *
 * <method> StpExpression simplify(e)                                         *
 * ========================================================================== */
PyObject* Stp_simplify(Stp *self, PyObject *args)
{
  return pair1Expression(self, args, vc_simplify);
}

/* ========================================================================== *
 * <method> Boolean query(e)                                                  *
 * ========================================================================== */
PyObject* Stp_query(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr;
  int retval;

  if(!PyArg_ParseTuple(args, "O!", &StpExpression_type, &pstpexpr))
    /* error parsing input parameters */
    return NULL;

  retval = vc_query(self->solver, pstpexpr->expr);

  switch(retval) {
  case 0:
    /* INVALID => return False */
    Py_RETURN_FALSE;
  case 1:
    /* VALID => return True */
    Py_RETURN_TRUE;
  case 2:
    /* ERROR => return None */
    Py_INCREF(Py_None);
    return Py_None;  
  default:
    /* this should never happen.. */
    return NULL;
  }
}

/* ========================================================================== *
 * <method> StpExpr getCounterExample(e)                                      *
 * ========================================================================== */
PyObject* Stp_getCounterExample(Stp *self, PyObject *args)
{
  return pair1Expression(self, args, vc_getCounterExample);
}

/* ========================================================================== *
 * <method> int counterExample_size()                                         *
 * ========================================================================== */
PyObject* Stp_counterExample_size(Stp *self)
{
  int size;

  size = vc_counterexample_size(self->solver);

  return PyInt_FromLong(size);
}

/* ========================================================================== *
 * <method> void push()                                                       *
 * ========================================================================== */
PyObject* Stp_push(Stp *self)
{
  vc_push(self->solver);

  Py_INCREF(Py_None);
  return Py_None;
}

/* ========================================================================== *
 * <method> void pop()                                                        *
 * ========================================================================== */
PyObject* Stp_pop(Stp *self)
{
  vc_pop(self->solver);

  Py_INCREF(Py_None);
  return Py_None;
}

/* ========================================================================== *
 * <method> void vc_setFlag(vc, c)                                            *
 * ========================================================================== */
PyObject* Stp_setFlags(Stp *self, PyObject *args)
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

    vc_setFlags(self->solver, c);
  }

  Py_INCREF(Py_None);
  return Py_None;
}

/* ========================================================================== *
 * <method> void deleteExpr(e)                                                *
 * ========================================================================== */
PyObject* Stp_deleteExpr(Stp *self, PyObject *args)
{
  StpExpression *pstpexpr;

  if(!PyArg_ParseTuple(args, "O!", &StpExpression_type, &pstpexpr))
    /* error parsing input parameters */
    return NULL;

  /* delete embedded Expr object */
  vc_DeleteExpr(pstpexpr->expr);

  /* delete StpExpr object */
  StpExpression_type.tp_dealloc((PyObject*) pstpexpr);

  Py_INCREF(Py_None);
  return Py_None;
}

/* ========================================================================== *
 * <method> void destroy()                                                    *
 * ========================================================================== */
PyObject* Stp_destroy(Stp *self)
{
  tpystp_node *p;

  DEBUG("[Stp@%p] destroying itself!\n", self->solver);
  /* delete embedded Stp object */
  vc_Destroy(self->solver);

  /* decrement references to embedded types/expressions, so that they can
     be garbage collected */
  for(p=self->types_list; p; p=p->next) {
    Py_DECREF((PyObject*) p->data);
  }

  for(p=self->exps_list; p; p=p->next) {
    Py_DECREF((PyObject*) p->data);
  }

  Py_INCREF(Py_None);
  return Py_None;
}

/* ==================================================================== */

void Stp_dealloc(Stp* self)
{
  self->ob_type->tp_free((PyObject*)self);
}

int Stp_init(Stp* self, PyObject *args, PyObject *kwds)
{
  self->solver = vc_createValidityChecker();

  /* init types/expressions lists */
  pystp_list_init(&self->types_list);
  pystp_list_init(&self->exps_list);

  return 0;
}
