/*
 * Player.h - Base class for a player.
 * Created January 26, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_O_PLAYER_H_
#define _ADENA_O_PLAYER_H_

#include <Pawn.h>
#include <SCharInfo.h>
#include <SItemInfo.h>

namespace adena
{
namespace game_server
{

	class Player : public Pawn
	{
	public:

		Player(IOObjectSystem* obj_sys);

		virtual ~Player();

		virtual void destroy();

		// Actions
		virtual void useSkill(irr::u32 skill_id, bool ctrl, bool shift);

		// Getters
		virtual irr::u32 getSpeed();

		virtual irr::u32 getLevel();

		virtual irr::f64 getMaxHp();
		virtual irr::f64 getHp();
		virtual irr::f64 getMaxMp();
		virtual irr::f64 getMp();
		virtual irr::f64 getMaxCp();
		virtual irr::f64 getCp();

		virtual irr::u32 getSTR();
		virtual irr::u32 getCON();
		virtual irr::u32 getDEX();
		virtual irr::u32 getINT();
		virtual irr::u32 getWIT();
		virtual irr::u32 getMEN();

		virtual irr::u32 getPAttack();
		virtual irr::f32 getAttackSpeed();
		virtual irr::f32 getAttackRange();

		virtual irr::u32 getMAttack();
		virtual irr::f32 getCastSpeed();
		virtual irr::f32 getCastRange();

		virtual irr::f32 getHpRegen();

		virtual irr::core::array<SSkill>* getSkills();
		virtual irr::core::array<CItemInstance>* getItems();

		// Setters
		virtual void addItem(SItemInfo* item, irr::u32 count);

		virtual void setHp(irr::f64 hp);
		virtual void setCp(irr::f64 cp);

		virtual void setXpSp(irr::u64 xp, irr::u64 sp);

		// Events
		virtual void onSeeObj(Actor* obj);

		virtual void onBeenSeen(Actor* obj);

		virtual void onLoseObj(Actor* obj);

		virtual void onBeenLost(Actor* obj);

		virtual irr::u32 onDoAttackDmg(Actor* target);

		// Timers
		virtual bool regenHpMpCp(void* data);

		// Utills
		virtual void saveToDatabase();

		SCharInfo* CharInfo;

	};

}
}

#endif
