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

#include <stdio.h>
#include <usb.h>
#include <sys/select.h>
#include <sys/time.h>
#include <curses.h>
#include <term.h>

#include "rl78com.h"

#define CONTROL(x)  ((x) & 0x1F)


void configure_screen () {
    	SCREEN *s = newterm(NULL, stdin, stdout);
    	if (s == 0)
    		exit(-1);
    	cbreak();
    	noecho();
    	keypad(stdscr, TRUE);
	setbuf(stdout, NULL);

}

int main(void)
{
	struct usb_dev_handle *myhandle;

	myhandle = find_rl78();

	if (myhandle != NULL) {
		fd_set s_rd;
		struct timeval delay;
		char ch, ch2;
		
		configure_rl78(myhandle);
		configure_screen();

		while (ch != EOF && ch != CONTROL('d')) {
			delay.tv_sec = 0;
			delay.tv_usec = 0;
			FD_ZERO(&s_rd);
 			FD_SET(fileno(stdin), &s_rd);

    			select(fileno(stdin)+1, &s_rd, NULL, NULL, &delay);
			if (FD_ISSET (fileno(stdin), &s_rd)) {
				ch=getch();
				if (ch != EOF && ch != CONTROL('d')) 
					rl78_write(myhandle, &ch, 1, 100);
			}

			int ret = rl78_read(myhandle, &ch2, 1, 50);
			if (ret >= 0) {
				putchar (ch2);
			} 
			
		}

		usb_close(myhandle);
    		endwin();
	}

	return 0;
}

