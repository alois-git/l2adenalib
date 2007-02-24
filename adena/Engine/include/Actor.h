/*
 * Actor.h - Base object for all objects with a location.
 * Created January 25, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_O_ACTOR_H_
#define _ADENA_C_O_ACTOR_H_

#include <COObject.h>
#include <irrList.h>
#include <vector3d.h>
#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class Actor : public COObject
	{
	public:

		Actor(IOObjectSystem* obj_sys);

		virtual ~Actor();

		Actor* spawn(irr::core::stringc obj, irr::core::vector3df location, irr::s32 heading);

		virtual void setLocation(irr::core::vector3df &location);

		virtual void broadcastPacket(IPacket* pack);

		/*
		 * @param event_instagator: [IN] Obj that did the damage.
		 * @param damage: [IN] Damage to be done [OUT] Damage actualy done.
		 * @param crit: [IN] Crit hit.
		 * @param shield: [IN] Shield blocked.
		 */
		virtual void takeDamage(Actor* event_instagator, irr::u32 &damage, bool crit, bool shield) {};

		// Events

		// Called when a controller clicks on this actor.
		virtual void onClick(COObject* event_instagator, bool shift_click);

		// Called when this actor sees another actor.
		virtual void onSeeObj(Actor* obj) {};

		// Called when this actor is seen by another actor.
		virtual void onBeenSeen(Actor* obj) {};

		// Called when this actor loses site of another actor.
		virtual void onLoseObj(Actor* obj) {};

		// Called when another actor loses site of this actor.
		virtual void onBeenLost(Actor* obj) {};

		irr::core::vector3df Location;
		irr::s32 Heading;

		// List of actors that this object is in range of (actors that need to be updated if the state of this actor changes).
		irr::core::list<Actor*> KnownList;

	};

}
}

#endif
