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

#ifndef _PYSTP_H
#define _PYSTP_H

#include <Python.h>
#include "pystp_stp.h"
#include "pystp_expr.h"
#include "pystp_type.h"

/* === Stp object === */

static PyMemberDef Stp_members[] = {
  {NULL}			/* Sentinel */
};

static PyMethodDef Stp_methods[] = {
  {"createType", (PyCFunction)Stp_createType, METH_VARARGS,
   "createType(type [, nelements])-> StpType\n"
   "Create a StpType object of the specified type."
   "The 'type' parameter can be set to one of the TYPE_* constants define inside pystp module."},

  {"varExpr", (PyCFunction)Stp_varExpr, METH_VARARGS,
   "varExpr(name, type) -> StpExpr\n"
   "Create a variable with a given name and type."
   "The variable name can contain only variables, numberals and underscore. If you use any other symbol, you will get a SEGFAULT."},

  {"varExpr1", (PyCFunction)Stp_varExpr1, METH_VARARGS,
   "varExpr1(name, indexwidth, valuewidth) -> StpExpr\n"
   "The variable name can contain onvly variables, numerals and underscore. If you use any other symbol, you will get a SEGFAULT."},

  {"eqExpr", (PyCFunction)Stp_eqExpr, METH_VARARGS,
   "eqExpr(expr_child0, expr_child1) -> StpExpr\n"
   "Create an equality expression with left child 'expr_child0' and right child 'expr_child1'."
   "The two children must have the same type."},

  {"trueExpr", (PyCFunction)Stp_trueExpr, METH_NOARGS,
   "trueExpr() -> StpExpr\nCreate a 'true' expression."},

  {"falseExpr", (PyCFunction)Stp_falseExpr, METH_NOARGS,
   "falseExpr() -> StpExpr\nCreate a 'false' expression."},

  {"notExpr", (PyCFunction)Stp_notExpr, METH_VARARGS,
   "notExpr(expr) -> StpExpr\n"
   "Return the StpExpression expression obtained by negating 'expr'."},

  {"andExpr", (PyCFunction)Stp_andExpr, METH_VARARGS,
   "andExpr([expr0, expr1, ..., exprN]) -> StpExpr\n"
   "Return the StpExpression expression that represents the conjunction of the given children expressions."},

  {"orExpr", (PyCFunction)Stp_orExpr, METH_VARARGS,
   "orExpr([expr0, expr1, ..., exprN]) -> StpExpr\n"
   "Return the StpExpression expression that represents the disjunction of the given children expressions."},

  {"impliesExpr", (PyCFunction)Stp_impliesExpr, METH_VARARGS,
   "impliesExpr(hyp, conc) -> StpExpr\n"
   "Return the StpExpression expression that represents the implication hyp => conc."},

  {"iffExpr", (PyCFunction)Stp_iffExpr, METH_VARARGS,
   "iffExpr(left, right) -> StpExpr\n"
   "If and only if?"},

  {"iteExpr", (PyCFunction)Stp_iteExpr, METH_VARARGS,
   "iteExpr(conditional, ifthenpart, elsepart) -> StpExpr\n"
   "The condition must always be Boolean, but the if-then part (resp. else part) can be bit-vector or Boolean type."
   "The if-then part and the else part must be both of the same type."
   "The output type of the ite expression can be Boolean (formula-level ite) or bit-vector (word-level ite)."},

  {"readExpr", (PyCFunction)Stp_readExpr, METH_VARARGS,
   "readExpr(array, index) -> StpExpr\n"
   "Create an expression for the value of array at the given index."},

  {"writeExpr", (PyCFunction)Stp_writeExpr, METH_VARARGS,
   "writeExpr(array, index, newValue) -> StpExpr\n"
   "Array update; equivalent to \"array WITH [index] := newValue\"."},

  {"printCounterExample", (PyCFunction)Stp_printCounterExample, METH_NOARGS,
   "printCounterExample() -> None\n"
   "Print counterexample to stdout."},

  {"printVarDecls", (PyCFunction)Stp_printVarDecls, METH_NOARGS,
   "printVarDecls() -> None\n"
   "Print variable declarations to stdout."},

  {"printAsserts", (PyCFunction)Stp_printAsserts, METH_NOARGS,
   "printAsserts() -> None\n"
   "Print asserts to stdout."},

  {"getQueryState", (PyCFunction)Stp_getQueryState, METH_VARARGS,
   "getQueryState(e) -> String\n"
   "Return a newly allocated String object that contains the state of the query for StpExpression 's'."
   "It is roughly equivalent to STP's vc_printQueryStateToBuffer() function."},

  /* BIT VECTOR OPERATIONS */

  {"bvConstExprFromStr", (PyCFunction)Stp_bvConstExprFromStr, METH_VARARGS,
   "bvConstExprFromStr(binary_repr) -> StpExpr\n"
   "Build a BitVector expression starting from the given binary representation ('binary_repr' must be string)."},

  {"bvConstExprFromInt", (PyCFunction)Stp_bvConstExprFromInt, METH_VARARGS,
   "bvConstExprFromInt(n_bits, value) -> StpExpr\n"
   "Build a 'n_bits' long bit vector, starting from the given binary representation ('value' must be an unsigned integer)."},

  {"bvConstExprFromLL", (PyCFunction)Stp_bvConstExprFromLL, METH_VARARGS,
   "bvConstExprFromLL(n_bits, value) -> StpExpr\n"
   "Build a 'n_bits' long bit vector, starting from the given binary representation ('value' must be an unsigned long long)."},

  {"bv32ConstExprFromInt", (PyCFunction)Stp_bv32ConstExprFromInt, METH_VARARGS,
   "bv32ConstExprFromInt(value) -> StpExpr\n"
   "Build a 32 long bit vector, starting from the given binary representation ('value' must be an unsigned integer)."},

  {"bvConcatExpr", (PyCFunction)Stp_bvConcatExpr, METH_VARARGS,
   "bvConcatExpr(left, right) -> StpExpr\n"
   "Concatenate expressions 'left' and 'right'."},

  {"bvPlusExpr", (PyCFunction)Stp_bvPlusExpr, METH_VARARGS,
   "bvPlusExpr(n_bits, left, right) -> StpExpr\n"
   "Add expressions together in a 'n_bits' bitvector."},

  {"bv32PlusExpr", (PyCFunction)Stp_bv32PlusExpr, METH_VARARGS,
   "bv32PlusExpr(left, right) -> StpExpr\n"
   "Add expressions together in a 32 bitvector."},

  {"bvMinusExpr", (PyCFunction)Stp_bvMinusExpr, METH_VARARGS,
   "bvMinusExpr(n_bits, left, right) -> StpExpr\n"
   "Subtract expressions together in a 'n_bits' bitvector."},

  {"bv32MinusExpr", (PyCFunction)Stp_bv32MinusExpr, METH_VARARGS,
   "bv32MinusExpr(left, right) -> StpExpr\n"
   "Subtract expressions together in a 32 bitvector."},

  {"bvMultExpr", (PyCFunction)Stp_bvMultExpr, METH_VARARGS,
   "bvMultExpr(n_bits, left, right) -> StpExpr\n"
   "Add expressions together in a 'n_bits' bitvector."},

  {"bv32MultExpr", (PyCFunction)Stp_bv32MultExpr, METH_VARARGS,
   "bv32MultExpr(left, right) -> StpExpr\n"
   "Multiply expressions together in a 32 bitvector."},

  {"bvDivExpr", (PyCFunction)Stp_bvDivExpr, METH_VARARGS,
   "bvDivExpr(n_bits, left, right) -> StpExpr\n"
   "Divide expressions together in a 'n_bits' bitvector."},

  {"bvLtExpr", (PyCFunction)Stp_bvLtExpr, METH_VARARGS,
   "bvLtExpr(left, right) -> StpExpr\n"
   "Build a 'less than' expression with the given left and right children."},

  {"bvLeExpr", (PyCFunction)Stp_bvLeExpr, METH_VARARGS,
   "bvLeExpr(left, right) -> StpExpr\n"
   "Build a 'less than or equal to' expression with the given left and right children."},

  {"bvGtExpr", (PyCFunction)Stp_bvGtExpr, METH_VARARGS,
   "bvGtExpr(left, right) -> StpExpr\n"
   "Build a 'greater than' expression with the given left and right children."},

  {"bvGeExpr", (PyCFunction)Stp_bvGeExpr, METH_VARARGS,
   "bvGeExpr(left, right) -> StpExpr\n"
   "Build a 'greater than or equal to' expression with the given left and right children."},

  {"sbvLtExpr", (PyCFunction)Stp_sbvLtExpr, METH_VARARGS,
   "sbvLtExpr(left, right) -> StpExpr\n"
   "Build a 'signed less than' expression with the given left and right children."},

  {"sbvLeExpr", (PyCFunction)Stp_sbvLeExpr, METH_VARARGS,
   "sbvLeExpr(left, right) -> StpExpr\n"
   "Build a 'signed less than or equal to' expression with the given left and right children."},

  {"sbvGtExpr", (PyCFunction)Stp_sbvGtExpr, METH_VARARGS,
   "sbvGtExpr(left, right) -> StpExpr\n"
   "Build a 'signed greater than' expression with the given left and right children."},

  {"sbvGeExpr", (PyCFunction)Stp_sbvGeExpr, METH_VARARGS,
   "sbvGeExpr(left, right) -> StpExpr\n"
   "Build a 'signed greater than or equal to' expression with the given left and right children."},

  {"bvUMinusExpr", (PyCFunction)Stp_bvUMinusExpr, METH_VARARGS,
   "bvUMinusExpr(child) -> StpExpr\n"
   "Prepend bit-vector expression with an unary minus."},

  {"bvAndExpr", (PyCFunction)Stp_bvAndExpr, METH_VARARGS,
   "bvAndExpr(left, right) -> StpExpr\n"
   "Return 'left' AND 'right'."},

  {"bvOrExpr", (PyCFunction)Stp_bvOrExpr, METH_VARARGS,
   "bvOrExpr(left, right) -> StpExpr\n"
   "Return 'left' OR 'right'."},

  {"bvXorExpr", (PyCFunction)Stp_bvXorExpr, METH_VARARGS,
   "bvXorExpr(left, right) -> StpExpr\n"
   "Return 'left' XOR 'right'."},

  {"bvNotExpr", (PyCFunction)Stp_bvNotExpr, METH_VARARGS,
   "bvNotExpr(child) -> StpExpr\n"
   "Return NOT 'child'."},

  {"bvLeftShiftExpr", (PyCFunction)Stp_bvLeftShiftExpr, METH_VARARGS,
   "bvLeftShiftExpr(sh_amt, child) -> StpExpr\n"
   "Return 'child' shifted left of 'sh_amt' bits."},

  {"bvRightShiftExpr", (PyCFunction)Stp_bvRightShiftExpr, METH_VARARGS,
   "bvRightShiftExpr(sh_amt, child) -> StpExpr\n"
   "Return 'child' shifted right of 'sh_amt' bits."},

  {"bvExtract", (PyCFunction)Stp_bvExtract, METH_VARARGS,
   "bvExtract(child, high_bit_no, low_bit_no) -> StpExpr\n"
   "Extract from 'child' bits from 'low_bit_no' to 'high_bit_no'."},

  {"bvBoolExtract", (PyCFunction)Stp_bvBoolExtract, METH_VARARGS,
   "bvBoolExtract(x, bit_no) -> StpExpr\n"
   "Accept a bitvector and a position and return a boolean corresponding to that position."
   "More precisely, it returns the equation (x[bit_no:bit_no] = 0)."},

  {"bvSignExtend", (PyCFunction)Stp_bvSignExtend, METH_VARARGS,
   "bvSignExtend(child, nbits) -> StpExpr\n"
   "Perform sign extension to 'nbits'."},

  {"bvCreateMemoryArray", (PyCFunction)Stp_bvCreateMemoryArray, METH_VARARGS,
   "bvCreateMemoryArray(arrayName) -> StpExpr\n"
   "Create a memory array with the given name."},

  {"bvReadMemoryArray", (PyCFunction)Stp_bvReadMemoryArray, METH_VARARGS,
   "bvCreateMemoryArray(array, byteIndex, numOfBytes) -> StpExpr\n"
   "Read 'numOfBytes' bytes from the array 'array', starting from index 'byteIndex'."},

  {"bvWriteToMemoryArray", (PyCFunction)Stp_bvWriteToMemoryArray, METH_VARARGS,
   "bvWriteToMemoryArray(array, byteIndex, element, numOfBytes) -> StpExpr\n"
   "Write the 'numOfBytes'-bytes long element 'element' to array 'array', starting from index 'byteIndex'."},

  /* CONTEXT-RELATED METHODS */

  {"assertFormula", (PyCFunction)Stp_assertFormula, METH_VARARGS,
   "assertFormula(e) -> None\n"
   "Assert a new formula in the current context. The formula must have Boolean type."},

  {"simplify", (PyCFunction)Stp_simplify, METH_VARARGS,
   "simplify(e) -> None\n"
   "Simplify the StpExpression 'e' with respect to the current context."},

  {"query", (PyCFunction)Stp_query, METH_VARARGS,
   "query(e) -> Boolean\n"
   "Check validity of e in the current context, where 'e' is a FORMULA."
   "Return True (input is INVALID), False (input is VALID) or None (ERROR)."},

  {"getCounterExample", (PyCFunction)Stp_getCounterExample, METH_VARARGS,
   "getCounterExample(e) -> StpExpr\n"
   "Return the counterexample after a valid query."},

  {"counterExample_size", (PyCFunction)Stp_counterExample_size, METH_NOARGS,
   "counterExample_size() -> Long\n"
   "Get size of counterexample, i.e. the number of variables/array locations in the counterexample."},

  {"push", (PyCFunction)Stp_push, METH_NOARGS,
   "push(e) -> None\n"
   "Checkpoint the current context and increase the scope level."},

  {"pop", (PyCFunction)Stp_pop, METH_NOARGS,
   "pop(e) -> None\n"
   "Restore the current context to its state at the last checkpoint."},

  {"setFlags", (PyCFunction)Stp_setFlags, METH_VARARGS,
   "setFlags(e, flags) -> None\n"
   "Set the specified constraints solver flags ('flags' must be a string)."},

  {"deleteExpr", (PyCFunction)Stp_deleteExpr, METH_VARARGS,
   "deleteExpr(e) -> None\n"
   "Deletes the expression 'e'."},

  {"destroy", (PyCFunction)Stp_destroy, METH_NOARGS,
   "destroy() -> None\n"
   "Destroys the STP instance and removes all the created expressions."},

  {NULL}			/* Sentinel */
};

PyTypeObject Stp_type = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "pystp.Stp",               /*tp_name*/
  sizeof(Stp),               /*tp_basicsize*/
  0,                         /*tp_itemsize*/
  (destructor)Stp_dealloc,   /*tp_dealloc*/
  0,                         /*tp_print*/
  0,                         /*tp_getattr*/
  0,                         /*tp_setattr*/
  0,                         /*tp_compare*/
  0,                         /*tp_repr*/
  0,                         /*tp_as_number*/
  0,                         /*tp_as_sequence*/
  0,                         /*tp_as_mapping*/
  0,                         /*tp_hash */
  0,                         /*tp_call*/
  0,                         /*tp_str*/
  0,                         /*tp_getattro*/
  0,                         /*tp_setattro*/
  0,                         /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT,        /*tp_flags*/
  "STP objects",             /* tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  Stp_methods,               /* tp_methods */
  Stp_members,               /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)Stp_init,        /* tp_init */
  0,                         /* tp_alloc */
  PyType_GenericNew,         /* tp_new */
};


/* === StpExpression object === */

static PyMemberDef StpExpression_members[] = {
  {NULL}			/* Sentinel */
};

static PyMethodDef StpExpression_methods[] = {
  {"getType", (PyCFunction)StpExpression_getType, METH_NOARGS,
   "getType() -> StpType\n"
   "Return the StpType object associated to this expression."},

  {"getBVInt", (PyCFunction)StpExpression_getBVInt, METH_NOARGS,
   "getBVInt() -> Long\n"
   "Return an int from a constant bitvector expression."},

  {"getBVUnsigned", (PyCFunction)StpExpression_getBVUnsigned, METH_NOARGS,
   "getBVUnsigned() -> Long\n"
   "Return an unsigned int from a constant bitvector expression."},

  {"getBVUnsignedLongLong", (PyCFunction)StpExpression_getBVUnsignedLongLong, METH_NOARGS,
   "getBVUnsignedLongLong() -> Long\n"
   "Return an unsigned long long int from a constant bitvector expression."},

  {"getBVLength", (PyCFunction)StpExpression_getBVLength, METH_NOARGS,
   "getBVLength() -> Long\n"
   "Get bit vector length of an expression."},

  {"getChild", (PyCFunction)StpExpression_getChild, METH_VARARGS,
   "getChild(i) -> Expr\n"
   "Return the ith child."},

  {"getDegree", (PyCFunction)StpExpression_getDegree, METH_NOARGS,
   "getDegree() -> Long\n"
   "Return the degree (number of children) of a node."},

  {"getExprKind", (PyCFunction)StpExpression_getExprKind, METH_NOARGS,
   "getExprKind() -> Long\n"
   "Return the expression kind of a node."},

  {"getExprType", (PyCFunction)StpExpression_getExprType, METH_NOARGS,
   "getExprType() -> Long\n"
   "Return the expression type of a node."},

  {"getVWidth", (PyCFunction)StpExpression_getVWidth, METH_NOARGS,
   "getVWidth() -> Long\n"
   "Return the value bit width of a node."},

  {"getIWidth", (PyCFunction)StpExpression_getIWidth, METH_NOARGS,
   "getIWidth() -> Long\n"
   "Return the index bit width of a node."},
  
  {"getName", (PyCFunction)StpExpression_getName, METH_NOARGS,
   "getName() -> String\n"
   "Return name of expression. must be a variable."},

  {"getID", (PyCFunction)StpExpression_getID, METH_NOARGS,
   "getID() -> Long\n"
   "Return the node ID of an Expr."},

  {NULL}			/* Sentinel */
};

PyTypeObject StpExpression_type = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "pystp.StpExpression",    /*tp_name*/
  sizeof(StpExpression),     /*tp_basicsize*/
  0,                         /*tp_itemsize*/
  (destructor)StpExpression_dealloc,   /*tp_dealloc*/
  0,                         /*tp_print*/
  0,                         /*tp_getattr*/
  0,                         /*tp_setattr*/
  0,                         /*tp_compare*/
  0,                         /*tp_repr*/
  0,                         /*tp_as_number*/
  0,                         /*tp_as_sequence*/
  0,                         /*tp_as_mapping*/
  0,                         /*tp_hash */
  0,                         /*tp_call*/
  StpExpression_str,         /*tp_str*/
  0,                         /*tp_getattro*/
  0,                         /*tp_setattro*/
  0,                         /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT,        /*tp_flags*/
  "STP Expression objects",  /* tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  StpExpression_methods,     /* tp_methods */
  StpExpression_members,     /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)StpExpression_init,        /* tp_init */
  0,                         /* tp_alloc */
  StpExpression_new,         /* tp_new */
};

/* === StpType object === */

static PyMemberDef StpType_members[] = {
  {NULL}			/* Sentinel */
};

static PyMethodDef StpType_methods[] = {
  {"isBool",      (PyCFunction)StpType_isBool,      METH_NOARGS, "Return True if this is a Bool Type object."},
  {"isBitVector", (PyCFunction)StpType_isBitVector, METH_NOARGS, "Return True if this is a BitVector Type object."},
  {"isArray",     (PyCFunction)StpType_isArray,     METH_NOARGS, "Return True if this is an Array Type object."},
  {NULL}			/* Sentinel */
};

PyTypeObject StpType_type = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "pystp.StpType",           /*tp_name*/
  sizeof(StpType),           /*tp_basicsize*/
  0,                         /*tp_itemsize*/
  (destructor)StpType_dealloc, /*tp_dealloc*/
  0,                         /*tp_print*/
  0,                         /*tp_getattr*/
  0,                         /*tp_setattr*/
  0,                         /*tp_compare*/
  0,                         /*tp_repr*/
  0,                         /*tp_as_number*/
  0,                         /*tp_as_sequence*/
  0,                         /*tp_as_mapping*/
  0,                         /*tp_hash */
  0,                         /*tp_call*/
  StpType_str,               /*tp_str*/
  0,                         /*tp_getattro*/
  0,                         /*tp_setattro*/
  0,                         /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT,        /*tp_flags*/
  "STP Type Type objects",   /* tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  StpType_methods,           /* tp_methods */
  StpType_members,           /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)StpType_init,        /* tp_init */
  0,                         /* tp_alloc */
  StpType_new,                /* tp_new */
};

#endif /* _PYSTP_H */
