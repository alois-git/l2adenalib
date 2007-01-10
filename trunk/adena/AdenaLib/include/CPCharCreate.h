/*
 * CPCharCreate.h - Create char.
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

#ifndef _ADENA_C_P_CHAR_CREATE_H_
#define _ADENA_C_P_CHAR_CREATE_H_

#include <CPacket.h>
#include <irrString.h>

namespace adena
{
namespace game_server
{

	class CPCharCreate : public CPacket
	{
	public:

		CPCharCreate(irr::c8* in_data)
		: CPacket(), Name("")
		{
			Data = in_data;
			ReadPointer++;
			rStrW(Name);
			Race = r32();
			Sex = r32();
			ClassId = r32();
			Int = r32();
			Str = r32();
			Con = r32();
			Men = r32();
			Dex = r32();
			Wit = r32();
			HairStyle = r32();
			HairColor = r32();
			Face = r32();
		};

		virtual ~CPCharCreate()
		{
			Data = 0;
		};

		virtual irr::c8* getData()
		{
			return NULL;
		};

		virtual irr::u32 getLen()
		{
			return 0;
		};

		irr::core::stringc Name;
		irr::u32 Race;
		irr::u32 Sex;
		irr::u32 ClassId;
		irr::u32 Int;
		irr::u32 Str;
		irr::u32 Con;
		irr::u32 Men;
		irr::u32 Dex;
		irr::u32 Wit;
		irr::u32 HairStyle;
		irr::u32 HairColor;
		irr::u32 Face;

	private:



	};

}
}

#endif
