/* Queue information for QoS
   Copyright (C) 2005 kedacom Yuanyi Zhang

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 2, or (at your
option) any later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifndef __QOS_SHOW_H
#define __QOS_SHOW_H

int class_info_show(struct vty*);
int queue_info_show(struct vty*);
int police_info_show(struct vty*);

int ifq_show(struct interface*, struct vty*);

#endif
