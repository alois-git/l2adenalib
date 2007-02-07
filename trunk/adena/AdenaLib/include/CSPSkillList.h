/*
 * CSPSkillList.h - Send the client their skills.
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

#ifndef _ADENA_C_S_P_SKILL_LIST_H_
#define _ADENA_C_S_P_SKILL_LIST_H_

#include <Player.h>
#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CSPSkillList : public CServerPacket
	{
	public:

		CSPSkillList(Player* player)
		: CServerPacket(), P(player)
		{
			Priority = EPP_LOW;
		};

		virtual ~CSPSkillList() {};

		virtual bool writePacket()
		{
			irr::core::array<SSkill>* skills = P->getSkills();
			resize(5 + (skills->size() * 13));

			w8(0x58);
			w32(skills->size());

			for(irr::u32 i = 0; i < skills->size(); i++)
			{
				SSkillInfo* si = P->Owner->Server->Interfaces.SkillCache->getSkill((*skills)[i].Id);
				if(si->Data["operateType"] == "OP_ACTIVE")
					w32(1);
				else
					w32(0);
				w32((*skills)[i].Level);
				w32((*skills)[i].Id);
				w8((*skills)[i].Enchant); // Enchant level
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

		Player* P;

	};

}
}

#endif
