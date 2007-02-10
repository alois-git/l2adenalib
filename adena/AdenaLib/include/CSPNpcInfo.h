/*
 * CSPNpcInfo.h - Npc info.
 * Created February 1, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_NPC_INFO_H_
#define _ADENA_C_S_P_NPC_INFO_H_

#include <Player.h>
#include <CServerPacket.h>
#include <NPC.h>

namespace adena
{
namespace game_server
{

	class CSPNpcInfo : public CServerPacket
	{
	public:

		CSPNpcInfo(NPC* npc)
		: CServerPacket(), Npc(npc)
		{
			Priority = EPP_NORMAL;
		};

		virtual ~CSPNpcInfo() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x16);

				w32(Npc->Id);
				w32(Npc->NPCInfo->Id + 1000000);
				w32(Npc->isAutoAttackable()); // Attackable
				w32(Npc->Location.X);
				w32(Npc->Location.Y);
				w32(Npc->Location.Z);
				w32(Npc->Heading);
				w32(0);
				w32(Npc->NPCInfo->Matk_spd);
				w32(Npc->NPCInfo->Atk_spd);
				w32(Npc->NPCInfo->Run_spd);
				w32(Npc->NPCInfo->Walk_spd);
				w32(Npc->NPCInfo->Run_spd); // Swim
				w32(Npc->NPCInfo->Walk_spd); // Swim
				w32(Npc->NPCInfo->Run_spd); // Fl
				w32(Npc->NPCInfo->Walk_spd); // Fl
				w32(Npc->NPCInfo->Run_spd); // Fly
				w32(Npc->NPCInfo->Walk_spd); // Fly
				wf(1.1);
				wf(Npc->NPCInfo->Atk_spd / 277.478340719);
				wf(Npc->NPCInfo->Collision_radius);
				wf(Npc->NPCInfo->Collision_height);
				w32(Npc->NPCInfo->Rhand);
				w32(0);
				w32(Npc->NPCInfo->Lhand);
				w8(1); // Name above npc: 1 = true
				w8(1);
				w8(0);
				w8(0);
				w8(0); // invisible ?? 0=false  1=true   2=summoned (only works if model has a summon animation)
				wStrW(Npc->NPCInfo->Name);
				wStrW(Npc->NPCInfo->Title);
				w32(0);
				w32(0);
				w32(0);  // Karma

				w32(0);  // Abnormal effects
				w32(0);
				w32(0);
				w32(0);
				w32(0);
				w8(0);

				w8(0);  // Team circle: 1 = blue, 2 = red 
				wf(0);
				wf(0);
				w32(0);
			}

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

	private:

		NPC* Npc;

	};

}
}

#endif
