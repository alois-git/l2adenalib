/*
 * CSPAttack.h - PWN!.
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

#ifndef _ADENA_C_S_P_ATTACK_H_
#define _ADENA_C_S_P_ATTACK_H_

#include <Actor.h>
#include <CServerPacket.h>
#include <irrList.h>

namespace adena
{
namespace game_server
{

	struct SHit
	{
		SHit(irr::u32 target_id, irr::u32 damage, bool miss, bool crit, bool shield, bool soulshot, irr::u32 grade)
		: Flags(0), TargetId(target_id), Damage(damage)
		{
            if (soulshot)	Flags |= 0x10 | grade;
            if (crit)		Flags |= 0x20;
            if (shield)		Flags |= 0x40;
            if (miss)		Flags |= 0x80;
		};

		irr::u32 TargetId;
		irr::u32 Damage;
		irr::u32 Flags;

	};

	class CSPAttack : public CServerPacket
	{
	public:

		CSPAttack(Actor* attacker)
		: CServerPacket(), Attacker(attacker)
		{
			Priority = EPP_URGENT;
		};

		virtual ~CSPAttack() {};

		void addHit(Actor* target, irr::u32 damage, bool miss, bool crit, bool shield)
		{
			SHit s(target->Id, damage, miss, crit, shield, false, 0);
			Hits.push_back(s);
		};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x05);
				w32(Attacker->Id);
				w32(Hits[0].TargetId);
				w32(Hits[0].Damage);
				w8(Hits[0].Flags);
				w32(Attacker->Location.X);
				w32(Attacker->Location.Y);
				w32(Attacker->Location.Z);
				w16(Hits.size() - 1);
				for(irr::u32 i = 1; i < Hits.size(); i++)
				{
					w32(Hits[i].TargetId);
					w32(Hits[i].Damage);
					w8(Hits[i].Flags);
				}
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

		Actor* Attacker;
		irr::core::array<SHit> Hits;

	};

}
}

#endif
