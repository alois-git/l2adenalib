/*
 * Pawn.h - Base class for any moving object in the game.
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

#ifndef _ADENA_O_PAWN_H_
#define _ADENA_O_PAWN_H_

#include <Actor.h>
#include <IGameServerClient.h>

namespace adena
{
namespace game_server
{

	enum E_PawnState
	{
		EPS_None = 0,
		EPS_Attacking,
		EPS_Casting,
		EPS_Dead
	};

	enum E_MoveState
	{
		EMS_Still = 0,
		EMS_Moving,
		EMS_Sitting,
		EMS_Walking
	};

	class Pawn : public Actor
	{
	public:

		Pawn(IOObjectSystem* obj_sys);

		virtual ~Pawn();

		virtual void destroy();

		virtual void tick(irr::f32 delta_time);

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

		virtual irr::u32 getPAttack() {return 0;};
		virtual irr::f32 getAttackSpeed() {return 0;};
		virtual irr::f32 getAttackRange() {return 0;};

		virtual irr::u32 getMAttack() {return 0;};
		virtual irr::f32 getCastSpeed() {return 0;};
		virtual irr::f32 getCastRange() {return 0;};

		virtual irr::f32 getHpRegen() {return 0;};

		virtual bool isAutoAttackable();
		virtual bool isDead();
		virtual bool isLooksDead();

		// Setters

		virtual void setHp(irr::f64 hp) {};
		virtual void setCp(irr::f64 cp) {};
		virtual void setXp(irr::u64 xp) {};

		virtual void moveToLocation(irr::core::vector3df Target);

		//virtual void teleportToLocation(irr::core::vector3di Target);

		virtual void attack(Actor* target, bool shift_click);

		virtual void useSkill(irr::u32 skill_id, bool ctrl, bool shift);

		virtual void takeDamage(Actor* event_instagator, irr::u32 &damage, bool crit, bool shield);

		// Timers

		virtual bool attackTimer(void* data);

		virtual bool skillTimer(void* data);

		// Events

		virtual irr::u32 onDoAttackDmg(Actor* target);

		virtual void onDeath(Actor* event_instagator);

		// Event called when MoveTarget reached.
		virtual void onStopMove();

		virtual void onClick(COObject* event_instagator, bool shift_click);

		irr::core::vector3df MoveTarget;
		E_MoveState MoveState;
		E_PawnState PawnState;
		// We don't need to check our height EVERY tick...
		irr::u32 LastZCheck;
		Actor* Target;

		// Stats
		irr::u32 Level;

		irr::f64 Cp;
		irr::f64 Hp;
		irr::f64 Mp;
		irr::u64 Xp;
		irr::u64 Sp;

		IGameServerClient* Owner;

		bool HpUpdated;
		bool CpUpdated;

	};

}
}

#endif
