/*
 * hexdump.cpp - Displays a character array as hex and ascii.
 * Created March 26, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_HEXDUMP_H_INCLUDED__
#define __IRR_HEXDUMP_H_INCLUDED__

namespace irr
{

template<class T>
void hexdumpT(c8* msg, int len)
{
	int i;
	for(i = 0; i < len; i++)
	{
		if((msg[i] & 0xff) > 0xf){
			printf("%x ", (msg[i] & 0xff));
		}else{
			printf("0%x ", (msg[i] & 0xff));
		}
		if(((i + 1) % 16) == 0)
		{
			for(int o = 0; o < 16; o++)
			{
				if(((msg[o + (i - 15)]) & 0xff) < 32){
					printf(".");
				}
				else{
					printf("%c", msg[o + (i - 15)]);
				}
				if(((o + 1) % 8) == 0)
				{
					printf(" ");
				}
			}
			printf("\n");
		}
	}
	// Here we have to handle the remader of len / 16.
	if(len % 16 != 0){
		for(i = 0; i < (16 - (len % 16)); i++)
		{
			printf("   ");
		}
		for(i = 0; i < (len % 16); i++)
		{
			if(((msg[(len - (len % 16)) + i]) & 0xff) < 32){
				printf(".");
			}
			else{
				printf("%c", msg[(len - (len % 16)) + i]);
			}
				if(((i + 1) % 8) == 0)
				{
					printf(" ");
				}
		}
		printf("\n");
	}
}

#define hexdump irr::hexdumpT<irr::c8>

}

#endif
