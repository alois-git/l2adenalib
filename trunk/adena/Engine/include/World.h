/*
 * World.h - Keeps track of all the nubs.
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

// DON'T USE THIS YET (I'll do it later :P)...

#ifndef _ADENA_C_O_WORLD_H_
#define _ADENA_C_O_WORLD_H_

#include <IPacket.h>
#include <COObject.h>
#include <vector3d.h>
#include <Actor.h>
#include <irrThread.h>
#include <AVL.h>

namespace adena
{
namespace game_server
{

	struct SRegion
	{
		irr::core::threads::ReadWriteLock RWLock;
		AVL<irr::u32, Actor*> Actors;
	};

	class World : public COObject
	{
	public:

		World(IOObjectSystem* obj_sys);

		virtual ~World();

		// Tell the world there's somthing new spawning.
		virtual void newObj(Actor* obj);

		virtual void removeObj(Actor* obj);

		// Inform the world that teh actor moved
		virtual void updateLoc(Actor* obj);

		/*
		 * @param distance: 0 = Server, 1 = Party, 2 = Clan, 3 = Alliance, all else = distance :P
		 */
		//virtual void broadcastPacket(IPacket* packet, Actor* origin, irr::u32 distance);

	protected:

		AVL<irr::u16, SRegion*> Regions;
		irr::core::threads::ReadWriteLock RegionsLock;

		// Hold the current actor region so we can look up the old one when it changes regions.
		AVL<Actor*, irr::u16> ActorRegions;
		irr::core::threads::ReadWriteLock ActorRegionsLock;

	};

}
}

#endif
