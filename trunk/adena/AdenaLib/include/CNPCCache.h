/*
 * CNPCCache.h - Loads all the npc types from the database and stores them.
 * Created February 6, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_NPC_CACHE_H_
#define _ADENA_C_NPC_CACHE_H_

#include <AdenaConfig.h>
#include <irrString.h>
#include <AVL.h>
#include <irrDb.h>
#include <irrArray.h>

namespace adena
{
namespace game_server
{
	
	struct SDropInfo
	{
		irr::u32 ItemId;
		irr::u32 Min;
		irr::u32 Max;
		irr::u32 Chance;
	};

	struct SNPCInfo
	{
		irr::u32 Id;
		irr::core::stringc Name;
		irr::core::stringc Title;
		irr::f32 Collision_radius;
		irr::f32 Collision_height;
		irr::u32 Level;
		irr::u32 Sex;
		irr::core::stringc SpawnClass;
		irr::u32 Atk_range;
		irr::u32 Hp;
		irr::u32 Mp;
		irr::f32 Hp_regen;
		irr::f32 Mp_regen;
		irr::u32 STR;
		irr::u32 CON;
		irr::u32 DEX;
		irr::u32 INT;
		irr::u32 WIT;
		irr::u32 MEN;
		irr::u32 Exp;
		irr::u32 Sp;
		irr::u32 Patk;
		irr::u32 Pdef;
		irr::u32 Matk;
		irr::u32 Mdef;
		irr::u32 Atk_spd;
		irr::u32 Aggro_range;
		irr::u32 Matk_spd;
		irr::u32 Rhand;
		irr::u32 Lhand;
		irr::u32 Armor;
		irr::u32 Walk_spd;
		irr::u32 Run_spd;
		irr::u32 Is_undead;
		irr::core::array<SDropInfo> DropInfo;
	};

	class ADENALIB_API CNPCCache
	{
	public:

		CNPCCache();

		~CNPCCache();

		void init(irr::db::IDatabase* db);

		SNPCInfo* getNPC(irr::u32 id);

	private:

		AVL<irr::u32, SNPCInfo*> NPCs;

	};

}
}

#endif
