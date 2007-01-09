/*
 * ip2bytes.h - Converts a "127.0.0.1" style ip into a 4 byte array.
 * Created March 29, 2006, by Michael 'Bigcheese' Spencer.
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
