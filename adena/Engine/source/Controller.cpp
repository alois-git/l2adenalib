/*
 * Controller.cpp - Controls pawns.
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

#include <Controller.h>
#include <CPUserInfo.h>
#include <CSPCreatureSay.h>
#include <GameManager.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_Controller(IOObjectSystem* obj_sys)
{
	return (COObject*)new Controller(obj_sys);
}
}

Controller::Controller(IOObjectSystem* obj_sys)
: COObject(obj_sys), OwnedPawn(0)
{

};

Controller::~Controller()
{

};

void Controller::posses(Pawn* pawn)
{
	OwnedPawn = pawn;
	Player* p = dynamic_cast<Player*>(pawn);
	if(p)
	{
		Owner->sendPacket(new CPUserInfo(p));
		p->Owner = Owner;
	}
};

void Controller::clickGround(irr::core::vector3df origin, irr::core::vector3df target, bool mouse_click)
{
	OwnedPawn->moveToLocation(target);
};

void Controller::clickObject(Actor* obj, bool shift_click)
{
	obj->onClick(this, shift_click);
};

void Controller::requestAttack(Actor* target, bool shift_click)
{
	OwnedPawn->attack(target, shift_click);
};

void Controller::sendText(irr::u32 say_type, irr::core::stringc &msg, irr::core::stringc &target)
{
	GameManager* gm = dynamic_cast<GameManager*>(Owner->Server->Interfaces.GameManager);
	if(gm)
	{
		gm->broadcastPacket(new CSPCreatureSay(OwnedPawn->Id, say_type, ((Player*)OwnedPawn)->CharInfo->Name, msg));
	}
};

}
}
