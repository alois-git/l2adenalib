/*
 * CSPMacroList.h - Send the client their macro list.
 * Created January 12, 2007, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
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
 * Michael Spencer - bigcheesegs@gmail.com
 */

#ifndef _ADENA_C_S_P_MACRO_LIST_H_
#define _ADENA_C_S_P_MACRO_LIST_H_

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CSPMacroList : public CServerPacket
	{
	public:

		CSPMacroList()
		: CServerPacket()
		{
			Priority = EPP_NORMAL;
		};

		virtual ~CSPMacroList() {};

		virtual bool writePacket()
		{
			w8(0xe7);
			
			w32(0x00); // Macro change revision (changes after each macro edition)
			w8(0x00);    // Unknown
			w8(0x00);    // Count of Macros
			w8(0x00);    // Are there any macros?
			
			/*if (there are macros)
			{
				w32(0x00); 	// Macro ID
				wStrW(); 	// Macro Name
				wStrW(); 	// Desc
				wStrW(); 	// Acronym
				w8();		// Icon
				
				w8();		// Commands
				
				for (;;)
				{
					w8(0x00);		// Index
					w8(1);	// Type  1 = skill, 3 = action, 4 = shortcut
					w32(0x00);	// Skill id
					w8(0x00);		// Shortcut id
					wStrW();	// Command name
				}
			}*/

			return true;
		};

		virtual irr::c8* getData()
		{
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	};

}
}

#endif
