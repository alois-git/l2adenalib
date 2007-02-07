/*
 * Actor.cpp - Base object for all objects with a location.
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

#include <Actor.h>
#include <os.h>
#include <Player.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_Actor(IOObjectSystem* obj_sys)
{
	return (COObject*)new Actor(obj_sys);
}
}

Actor::Actor(IOObjectSystem* obj_sys)
: COObject(obj_sys)
{

};

Actor::~Actor()
{

};

Actor* Actor::spawn(irr::core::stringc obj, irr::core::vector3df location, irr::s32 heading)
{
	Actor* a = dynamic_cast<Actor*>(COObject::spawn(obj));
	if(a)
	{
		a->Location = location;
		a->Heading = heading;
	}
	return a;
};

void Actor::setLocation(irr::core::vector3df &location)
{
	Location = location;
};

void Actor::broadcastPacket(IPacket* pack)
{
	pack->getRef();
	if(((CServerPacket*)pack)->writePacket())
	{
		irr::core::list<Actor*>::Iterator ittr(KnownList.begin());
		for(; ittr != KnownList.end(); ittr++)
		{
			Player* p = dynamic_cast<Player*>((*ittr));
			if(p)
			{
				p->Owner->sendPacket(pack);
			}
		}
	}
	pack->drop();
};

void Actor::onClick(COObject *event_instagator, bool shift_click)
{

};

}
}
