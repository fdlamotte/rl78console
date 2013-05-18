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

#include <usb.h>

#include "rl78com.h"

struct ctrl_char {
	int size; 
	char data [10];
};

struct ctrl_char ctrl_init [] = { 
{2, {0x03, 0x01}},
{2, {0x01, 0x03}},
{6, {0x00, 0x00, 0x96, 0x00, 0x00, 0x01}},
{2, {0x04, 0x00, 0x00}},
{2, {0x01, 0x03}},
{3, {0x02, 0x11, 0x13}},
{0, {0}}
};


struct usb_dev_handle * find_rl78 () {

	struct usb_bus *busses;
	struct usb_bus *bus;

	struct usb_device *mydev;

	usb_init();
	usb_find_busses();
	usb_find_devices();

	busses = usb_get_busses();
	for (bus = busses; bus; bus = bus->next) {
		struct usb_device *dev;
		for (dev = bus->devices; dev; dev = dev->next) {
			if (dev->descriptor.idVendor == 0x045b && dev->descriptor.idProduct == 0x0212) {
				mydev = dev;
			}

		}
	}

	return (mydev != NULL) ? usb_open(mydev) : NULL;
}

void configure_rl78 (struct usb_dev_handle *myhandle) {
	usb_clear_halt(myhandle, BULKOUT);
	usb_clear_halt(myhandle, BULKIN);

	/* sending configuration */
	int i;
	for (i=0; ctrl_init[i].size != 0; i++) 
		usb_control_msg(myhandle, 'S', 2, 0, 0, ctrl_init[i].data, ctrl_init[i].size, 100);
}
