/*
 * CPPressStart.h - Enter teh world of l2.
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

#ifndef _ADENA_C_P_PRESS_START_H_
#define _ADENA_C_P_PRESS_START_H_

#include <CClientPacket.h>
#include <CPCharSelected.h>

namespace adena
{
namespace game_server
{

	class CPPressStart : public CClientPacket
	{
	public:

		CPPressStart(irr::c8* in_data, IGameServerClient* client)
		: CClientPacket()
		{
			Client = client;
			Data = in_data;
			ReadPointer++;
			CharIndex = r32();
			Unknown1 = r16();
			Unknown2 = r32();
			Unknown3 = r32();
			Unknown4 = r32();

			Client->CharInfo = Client->Server->Interfaces.PlayerCache->loadChar(Client->CharSelectIds.CharIds[CharIndex]);
			if(Client->CharInfo->InUse != true || !(Client->CharSelectIds.Chars < CharIndex))
			{
				Client->CharId = Client->CharSelectIds.CharIds[CharIndex];
				Client->sendPacket(new CPCharSelected(&Client->Server->Interfaces, Client->CharSelectIds.CharIds[CharIndex]));
			}else
			{
				Client->CharId = 0;
			}
			delete this;
		};

		virtual ~CPPressStart()
		{
			Data = 0;
		};

		virtual void run()
		{
			
		};

		virtual irr::c8* getData()
		{
			return NULL;
		};

		virtual irr::u32 getLen()
		{
			return 0;
		};

		irr::u32 CharIndex;
		irr::u32 Unknown1;
		irr::u32 Unknown2;
		irr::u32 Unknown3;
		irr::u32 Unknown4;

	private:



	};

}
}

#endif
