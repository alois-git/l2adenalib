/*
 * CSPSkillLaunched.h - When a skill is done casting.
 * Created February 10, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_SKILL_LAUNCHED_H_
#define _ADENA_C_S_P_SKILL_LAUNCHED_H_

#include <Player.h>
#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CSPSkillLaunched : public CServerPacket
	{
	public:

		CSPSkillLaunched(Pawn* pawn, SSkill &skill)
		: CServerPacket(), P(pawn), Skill(skill)
		{
			Priority = EPP_HIGH;
		};

		virtual ~CSPSkillLaunched() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				w8(0x76);

				w32(P->Id);
				w32(Skill.Id);
				w32(Skill.Level);
				w32(0x00);  // Failed?
				w32(P->Target->Id);
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

		Pawn* P;
		SSkill Skill;

	};

}
}

#endif
