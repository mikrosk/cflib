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

/*
 * Ein eigener form_do(), der einige Sondertastentasten kann:
 * 
 * HELP     Button mit Flag11
 * UNDO     Button mit Flag12
 * ^C^V^X   Klemmbrett in Editfeldern
 * ALT-X    MagiC-Shortcut
 *
 */

#include "intern.h"


_WORD simple_dial(OBJECT *tree, _WORD start_edit)
{
	_WORD exit_obj;
	GRECT r;

	graf_mouse(ARROW, NULL);
	wind_update(BEG_UPDATE);
	form_center_grect(tree, &r);
	form_dial_grect(FMD_START, &r, &r);
	graf_mouse(M_OFF, NULL);
	objc_draw_grect(tree, ROOT, MAX_DEPTH, &r);
	graf_mouse(M_ON, NULL);
	exit_obj = cf_form_do(tree, &start_edit) & 0x7FFF;
	form_dial_grect(FMD_FINISH, &r, &r);
	wind_update(END_UPDATE);
	set_state(tree, exit_obj, OS_SELECTED, FALSE);

	return exit_obj;
}
