/*
 * CFLIB, a GEM library for ATARI/TOS
 * Copyright (C) 1999, 2000 Christian Felsch
 * 
 * Modified for FreeMiNT CVS by Frank Naumann <fnaumann@freemint.de>
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 * 
 */

#ifdef __MINT__
  #include <mintbind.h>
#else
  #include <tos.h>
#endif

#include "app.h"
#include "intern.h"


int
fs_case_sens (char *filename)
{
	char path[256];
	int ret;

	/* Eigentlichen Dateinamen abschneiden und durch '.' ersetzen -
	 * mu� sein, da Datei evtl. noch nicht existiert... */
	split_filename (filename, path, NULL);
	strcat (path, ".");
	ret = (int) Dpathconf (path, 6);

	/* MagiCPC 6.0 meldet 0, das ist aber falsch!! */
	if (cf_magxPC && ret == 0)
		ret = 2;

	switch (ret)
	{
		case 0:	/* echter Unterschied, MinixFS */
			ret = FULL_CASE;
			break;
		case 2:	/* kein echter Unterschied, VFAT, MacFS */
			ret = HALF_CASE;
			break;
		default:
			ret = NO_CASE;	/* Dpathconf() nicht verf�gbar, oder kein Unterschied */
	}
	return ret;
}