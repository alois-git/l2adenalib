/*
 * ip2bytes.h - Converts a "127.0.0.1" style ip into a 4 byte array.
 * Created March 29, 2006, by Michael 'Bigcheese' Spencer.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <ip2bytes.h>

void ip2bytes(char* ip, char out[4])
{
	int retplace = 0;
	char* hold = ip;
	char* move = ip;
	while(move[0] != 0){
		move++;
		if(move[0] == '.'){
			//move[0] == 0;
			out[retplace] = atoi(hold);
			retplace++;
			move++;
			hold = move;
		}
	}
	out[3] = atoi(hold);
}
