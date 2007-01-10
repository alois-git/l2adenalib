/*
 * CPCharTemplate.h - Char template packet.
 * Created January 7, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_P_CHAR_TEMPLATE_H_
#define _ADENA_C_P_CHAR_TEMPLATE_H_

#include <CPacket.h>
#include <irrList.h>
#include <SClassTemplate.h>

namespace adena
{
namespace game_server
{

	class CPCharTemplate : public CPacket
	{
	public:

		CPCharTemplate(irr::core::list<SClassTemplate> &list)
		: CPacket()
		{
			w8(0x17);
			w32(list.getSize());

			irr::core::list<SClassTemplate>::Iterator ittr;
			for (ittr = list.begin(); ittr != list.end(); ittr++)
			{
				/*w32(temp.race.ordinal());
				w32(temp.classId.getId());
				w32(0x46);
				w32(temp.baseSTR);
				w32(0x0a);
				w32(0x46);
				w32(temp.baseDEX);
				w32(0x0a);
				w32(0x46);
				w32(temp.baseCON);
				w32(0x0a);
				w32(0x46);
				w32(temp.baseINT);
				w32(0x0a);
				w32(0x46);
				w32(temp.baseWIT);
				w32(0x0a);
				w32(0x46);
				w32(temp.baseMEN);
				w32(0x0a);*/
			}
		};

		virtual ~CPCharTemplate()
		{

		};

		virtual irr::c8* getData()
		{
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	private:



	};

}
}

#endif
