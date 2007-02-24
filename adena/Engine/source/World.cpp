/*
 * World.cpp - Keeps track of all the nubs.
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

#include <World.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_World(IOObjectSystem* obj_sys)
{
	return (COObject*)new World(obj_sys);
}
}

World::World(IOObjectSystem* obj_sys)
: COObject(obj_sys)
{

};

World::~World()
{

};

// World cords
irr::u16 getRegion(irr::u32 x, irr::u32 y)
{
	x = ((irr::s32)x - MAP_MIN_X) >> 4;
	y = ((irr::s32)y - MAP_MIN_Y) >> 4;
	x = x >> 11; // =/(256 * 8)
	y = y >> 11;
	return (((x+16) << 5) + (y+10));
};

/*
 * @param x: [IN] World x [OUT] region x.
 * @param y: [IN] World y [OUT] region y.
 * Converts World cords into region x/y (ex. 17_25).
 */
void getRegionXY(irr::u32 &x, irr::u32 &y)
{
	x = ((irr::s32)x - MAP_MIN_X) >> 4;
	y = ((irr::s32)y - MAP_MIN_Y) >> 4;
	x = x >> 11; // =/(256 * 8)
	y = y >> 11;
	x += 16;
	y += 10;
};

void World::newObj(Actor *obj)
{
	irr::u16 region = getRegion(obj->Location.X, obj->Location.Y);
	SRegion* r = 0;
	RegionsLock.readLock();
	if(Regions.Find(region, r))
	{
		RegionsLock.unlock();
		// Insert into teh region
		r->RWLock.writeLock();
		r->Actors.Insert(obj->Id, obj);
		r->RWLock.unlock();

		ActorRegionsLock.writeLock();
		ActorRegions.Insert(obj, region);
		ActorRegionsLock.unlock();

		// Add self to known list.
		obj->KnownList.push_back(obj);
		// Update known list.
		updateLoc(obj);
	}else
	{
		SRegion* r = new SRegion();
		r->Actors.Insert(obj->Id, obj);
		RegionsLock.unlock();
		RegionsLock.writeLock();
		Regions.Insert(region, r);
		RegionsLock.unlock();
	}
};

void World::removeObj(Actor* obj)
{
	irr::u16 region = getRegion(obj->Location.X, obj->Location.Y);
	SRegion* r = 0;
	RegionsLock.readLock();
	if(Regions.Find(region, r))
	{
		RegionsLock.unlock();
		r->RWLock.writeLock();
		r->Actors.Remove(obj->Id);
		r->RWLock.unlock();

		ActorRegionsLock.writeLock();
		ActorRegions.Remove(obj);
		ActorRegionsLock.unlock();

		// Tell everyone that they can no longer see this obj.
		irr::core::list<Actor*>::Iterator ittr(obj->KnownList.begin());
		for(;ittr != obj->KnownList.end(); ittr++)
		{
			updateLoc((*ittr));
		}
		obj->KnownList.clear();
	}else
	{
		// Not here...
		RegionsLock.unlock();
	}
};

void World::updateLoc(Actor *obj)
{
	irr::u16 region = getRegion(obj->Location.X, obj->Location.Y);
	SRegion* r = 0;
	RegionsLock.readLock();
	if(Regions.Find(region, r))
	{
		RegionsLock.unlock();
		r->RWLock.readLock();
		Actor* a;
		if(r->Actors.Find(obj->Id, a))
		{
			// Hasn't changed regions
			r->RWLock.unlock();
		}else
		{
			// Has changed regions
			ActorRegionsLock.writeLock();

			irr::u16 reg = 0;
			if(ActorRegions.Find(obj, reg))
			{
				SRegion* re = 0;
				RegionsLock.readLock();
				if(Regions.Find(reg, re))
				{
					RegionsLock.unlock();
					// Get a lock on both regions so we can move the actor.
					re->RWLock.writeLock();
					r->RWLock.writeLock();

					re->Actors.Remove(obj->Id);
					r->Actors.Insert(obj->Id, obj);

					re->RWLock.unlock();
					r->RWLock.unlock();

					// Update the current region.
					ActorRegions.Remove(obj);
					ActorRegions.Insert(obj, region);
				}else
				{
					RegionsLock.unlock();
				}
			}
			ActorRegionsLock.unlock();
		}
		// Update known list.
		irr::u32 regionX = obj->Location.X;
		irr::u32 regionY = obj->Location.Y;
		getRegionXY(regionX, regionY);

		irr::core::array<Actor*> TempKnownList;
		for(irr::s32 rx = regionX - 1; rx <= regionX + 1; rx++)
		{
			for(irr::s32 ry = regionY - 1; ry <= regionY + 1; ry++)
			{
				irr::u16 temp_region = ((rx << 5) + ry);
				SRegion* temp_r;

				RegionsLock.readLock();
				if(Regions.Find(temp_region, temp_r))
				{
					RegionsLock.unlock();
					// Iterate though actors and get everything in range.
					AVL<irr::u32, Actor*>::Iterator<irr::u32, Actor*> ittr(&temp_r->Actors);
					irr::u32 key;
					Actor* item;
					temp_r->RWLock.readLock();
					if(ittr.GetFirst(key, item))
					{
						while(true)
						{
							if(item != obj) // Don't want to include our selves
							{
								irr::f64 dist = item->Location.getDistanceFrom(obj->Location);
								if(dist <= MAX_VIEW_DIST)
								{
									// It's in range!
									TempKnownList.push_back(item);
								}
							}
							if(!ittr.GetNext(key, item))
								break;
						}
					}
					temp_r->RWLock.unlock();
				}
				else
				{
					RegionsLock.unlock();
				}
			}
		}
		// Now that we have filled the temp known list, update the real one.
		irr::u32 i;
		for(i = 0; i < TempKnownList.size(); i++)
		{
			bool in_list = false;
			irr::core::list<Actor*>::Iterator ittr(obj->KnownList.begin());
			for(;ittr != obj->KnownList.end(); ittr++)
			{
				if((*ittr) == TempKnownList[i])
				{
					// Already in the list.
					in_list = true;
					break;
				}
			}
			if(!in_list)
			{
				// Found new obj.
				obj->KnownList.push_back(TempKnownList[i]);
				TempKnownList[i]->KnownList.push_back(obj);
				obj->onSeeObj(TempKnownList[i]);
				TempKnownList[i]->onBeenSeen(obj);
				TempKnownList[i]->onSeeObj(obj);
				obj->onBeenSeen(TempKnownList[i]);
			}
		}
		// Look for objs we have lost site of
		TempKnownList.push_back(obj); // Add self.
		irr::core::list<Actor*>::Iterator ittr(obj->KnownList.begin());
		for(;ittr != obj->KnownList.end(); ittr++)
		{
			bool in_list = false;
			for(i = 0; i < TempKnownList.size(); i++)
			{
				if(TempKnownList[i] == (*ittr))
				{
					in_list = true;
					break;
				}
			}
			if(!in_list)
			{
				obj->onLoseObj((*ittr));
				(*ittr)->onBeenLost(obj);
				obj->KnownList.erase(ittr);
				ittr = obj->KnownList.begin();
			}
		}
	}else
	{
		// This region has yet to be created.
		RegionsLock.unlock();
		SRegion* r = new SRegion();
		r->Actors.Insert(obj->Id, obj);
		RegionsLock.unlock();
		RegionsLock.writeLock();
		Regions.Insert(region, r);
		RegionsLock.unlock();

		ActorRegionsLock.writeLock();
		ActorRegions.Insert(obj, region);
		ActorRegionsLock.unlock();
	}
};

}
}
