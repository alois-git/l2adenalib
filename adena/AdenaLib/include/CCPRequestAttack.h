/*
 * CCPRequestAttack.h - Client wants to pwn some nubs.
 * Created January 30, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_C_P_REQUEST_ATTACK_H_
#define _ADENA_C_C_P_REQUEST_ATTACK_H_

#include <GameManager.h>
#include <Controller.h>
#include <CClientPacket.h>
#include <CSPSocial.h>

namespace adena
{
namespace game_server
{

	class CCPRequestAttack : public CClientPacket
	{
	public:

		CCPRequestAttack(irr::c8* in_data, IGameServerClient* client)
		: CClientPacket()
		{
			Client = client;
			Data = in_data;
			ReadPointer++;

			irr::u32 targetId = r32();
			irr::s32 x = r32();
			irr::s32 y = r32();
			irr::s32 z = r32();
			bool shiftClick = r8();

			Controller* c = (Controller*)Client->PController;
			Actor* target = (Actor*)Client->Server->Interfaces.ObjectSystem->getObj(targetId);
			if(target == 0)
				puts("Client tried to atk an obj thats not in the server...");
			else
				c->requestAttack(target, shiftClick);
		};

		virtual ~CCPRequestAttack()
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

	};

}
}

#endif
