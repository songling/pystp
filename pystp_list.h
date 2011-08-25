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

#ifndef _PYSTP_LIST_H
#define _PYSTP_LIST_H

struct struct_pystp_node {
  void *data;			                /* the actual data object */
  struct struct_pystp_node *next;		/* pointer to the next element of this list */
};

typedef struct struct_pystp_node tpystp_node;

void pystp_list_init(tpystp_node**);
void pystp_list_addNode(tpystp_node**, void*);

#endif /* _PYSTP_LIST_H */
