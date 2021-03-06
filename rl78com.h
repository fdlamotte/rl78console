/*
 * rl78console
 * Copyright (C) 2013 Florent de Lamotte <florent.lamotte@univ-ubs.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef _RL78COM_H_
#define _RL78COM_H_

#include <usb.h>

#define BULKOUT 0x02
#define BULKIN 0x81


#define rl78_write(h,s,l,t) (usb_bulk_write((h), BULKOUT, (s), (l), (t)))
#define rl78_read(h,s,l,t) (usb_bulk_read((h), BULKIN, (s), (l), (t)))

struct usb_dev_handle * find_rl78 ();

void configure_rl78 (struct usb_dev_handle *myhandle);


#endif
