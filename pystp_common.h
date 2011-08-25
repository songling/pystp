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

#ifndef _PYSTP_COMMON_H
#define _PYSTP_COMMON_H

#include <Python.h>

#include "c_interface.h"
#include "pystp_type.h"
#include "pystp_expr.h"

/* if defined, debug mode is enabled */
#define DEBUG_MODE

#define TYPE_BOOL           0
#define TYPE_ARRAY          1
#define TYPE_BITVECTOR      2

/* ============== */
/* === MACROS === */
/* ============== */

/* DEBUG(const char*, ...) -- print debug information if DEBUG_MODE is set; otherwise do nothing */
#ifdef DEBUG_MODE
#include <stdio.h>
#define DEBUG(...) { fprintf(stderr, "\x1b[0;31m"); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\x1b[0m"); fflush(stderr); }
#else
#define DEBUG(...) { }
#endif /* DEBUG_MODE */

/* ================= */
/* === FUNCTIONS === */
/* ================= */

StpType* create_StpType(Stp*, Type);
StpType* create_StpType_noref(Stp*, Type);
StpExpression* create_StpExpr(Stp*, Expr);

void strrighttrim(char*);

#endif /* _PYSTP_COMMON_H */
