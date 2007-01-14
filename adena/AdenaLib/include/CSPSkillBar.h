/*
 * CSPSkillBar.h - Send the client their skill bar.
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

#ifndef _ADENA_C_S_P_SKILL_BAR_H_
#define _ADENA_C_S_P_SKILL_BAR_H_

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CSPSkillBar : public CServerPacket
	{
	public:

		CSPSkillBar()
		: CServerPacket()
		{
			Priority = EPP_NORMAL;
		};

		virtual ~CSPSkillBar() {};

		virtual bool writePacket()
		{
			w8(0x45);
			w32(0x00); // Num skills

			/*for(;;)
			{
				w32(0x01); // Type 1 = Item, 2 = Skill, 3 = Action, 4 = Macro, 5 = Recipe
				w32(0x00); // slot + (page * 12)

				switch() // Type
				{
				case 1: //1
            		w32(0x00); // Item id
            		break;
				case 2: //2
            		w32(0x00); // Skill id
            		w32(0x00); // Skill lvl
            		w8(0x00); // C5 
            		break;
				case 3: //3
            		w32(0x00); // Id
            		break;
				case 4: //4
            		w32(0x00); // Id
            		break;
				case 5: //5
            		w32(0x00); // Id
            		break;
				default:
            		w32(0x00); // id
				}
	            
				writeD(1); //??
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
