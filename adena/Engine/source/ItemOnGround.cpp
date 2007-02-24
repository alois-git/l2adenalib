/*
 * ItemOnGround.cpp - An item on the ground.
 * Created February 20, 2007, by Michael 'Bigcheese' Spencer.
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

#include <Controller.h>
#include <ItemOnGround.h>
#include <CSPDeleteObj.h>
#include <Player.h>
#include <CSPDropItem.h>
#include <CSPSystemMessage.h>
#include <CGameServer.h>
#include <GameManager.h>
#include <CSPGetItem.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_ItemOnGround(IOObjectSystem* obj_sys)
{
	return (COObject*)new ItemOnGround(obj_sys);
}
}

ItemOnGround::ItemOnGround(IOObjectSystem* obj_sys)
: Actor(obj_sys), Dropper(0), ItemInfo(0)
{

};

ItemOnGround::~ItemOnGround()
{

};

void ItemOnGround::onClick(COObject* event_instagator, bool shift_click)
{
	if(ItemCount != 0)
	{
		Controller* c = dynamic_cast<Controller*>(event_instagator);
		if(c)
		{
			if(c->OwnedPawn->Location.getDistanceFrom(Location) > 25)
				c->OwnedPawn->moveToLocation(Location);
			else
			{
				// TODO: Pickup item
				((Player*)c->OwnedPawn)->addItem(ItemInfo, ItemCount);
				ItemCount = 0;
				broadcastPacket(new CSPGetItem(this, c->OwnedPawn->Id));

				GameManager* gm = (GameManager*)CGameServer::getGMInstance();
				gm->L2World->removeObj(this);
				drop();
			}
		}
	}
};

void ItemOnGround::onBeenSeen(Actor* obj)
{
	Player* p = dynamic_cast<Player*>(obj);
	if(p)
		p->Owner->sendPacket(new CSPDropItem(Dropper, this));
};

void ItemOnGround::onBeenLost(Actor* obj)
{
	Player* p = dynamic_cast<Player*>(obj);
	if(p)
		p->Owner->sendPacket(new CSPDeleteObj(Id));
};

}
}
