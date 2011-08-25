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

#include <stdlib.h>
#include <stdio.h>
#include "pystp_list.h"

void pystp_list_init(tpystp_node **plist)
{
  *plist = 0;
}

void pystp_list_addNode(tpystp_node **phead, void *data)
{
  tpystp_node *newNode;

  newNode = (tpystp_node*) malloc(sizeof(tpystp_node));
  if(!newNode) {
    fprintf(stderr, "[pylist_addNode()] - dynamic allocation error.\n");
    exit(-1);
  }

  newNode->data = data;
  newNode->next = *phead;	/* its still ok even if *phead == 0 */

  *phead = newNode;		/* insert this node in front of the list */
}
