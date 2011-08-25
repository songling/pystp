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
#include <ctype.h>
#include <string.h>

#include "pystp_list.h"
#include "pystp_common.h"
#include "pystp_stp.h"
#include "pystp_type.h"
#include "pystp_expr.h"

extern PyTypeObject StpType_type;
extern PyTypeObject StpExpression_type;

void strrighttrim(char *s)
{
  int len;
  char *p;

  if(!s || (len = strlen(s)) == 0)
    /* nothing to do */
    return;
  
  for(p = s+len-1; p >= s && isspace(*p); p--)
    *p = '\0';
}

/* create_stptype_noref(Stp*, Type) -- creates a new StpType object, associated to the
 * specified Type instance. This one does not handle reference count. */

StpType* create_StpType_noref(Stp *pstp_stp, Type t)
{
  StpType *pstp_type;

  /* allocate a new StpType object */
  pstp_type = (StpType*) StpType_type.tp_alloc((PyTypeObject*) &StpType_type, 0);

  if(pstp_type == NULL)
    return NULL;

  /* associate to the newly created object the previously allocated Type instance */
  pstp_type->type = t;

  pstp_type->stp_stp  = pstp_stp;
  Py_INCREF(pstp_stp);
  DEBUG(" * created Type %p [linked to Stp@%p];\n", pstp_type->type, pstp_stp->solver);

  return pstp_type;
}

/* like the previous one, but handling reference count. */
StpType* create_StpType(Stp *pstp_stp, Type t)
{
  StpType *pstp_type;

  pstp_type = create_StpType_noref(pstp_stp, t);

  /* error checking */
  if(!pstp_type)
    return NULL;

  /* this reference will be decremented when the StpType object is deallocated */
  Py_INCREF(pstp_type);
  DEBUG(" * linked Stp@%p to Type %p\n", pstp_stp->solver, pstp_type->type);

  /* add this StpType object to Stp's list, so that we can decrement its
     reference count when the Stp object is deallocated. */
  pystp_list_addNode(&(pstp_stp->types_list), pstp_type);

  return pstp_type;
}

/* create_StpExpr(Stp*, Expr) -- creates a new StpExpression object, 
 * associated to the specified Expr instance. */

StpExpression* create_StpExpr(Stp *pstp_stp, Expr e)
{
  StpExpression *pstp_expr;

  /* allocate a new StpExpression object */
  pstp_expr = (StpExpression*) StpExpression_type.tp_alloc((PyTypeObject*) &StpExpression_type, 0);

  if(pstp_expr == NULL)
    return NULL;

  /* associate to the newly created object the previously allocated Expr instance */
  pstp_expr->expr = e;

  pstp_expr->stp_stp  = pstp_stp;
  /* this reference will be decremented when the StpExpression object is deallocated */
  Py_INCREF(pstp_stp);
  Py_INCREF(pstp_expr);

  DEBUG(" * linking Expr%p <-> Stp%p;\n", pstp_expr->expr, pstp_stp->solver); \
  /* add this StpExpression object to Stp's list, so that we can decrement its
     reference count when the Stp object is deallocated. */
  pystp_list_addNode(&(pstp_stp->exps_list), pstp_expr);

  return pstp_expr;
}


