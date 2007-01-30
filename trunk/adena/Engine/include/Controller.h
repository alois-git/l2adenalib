/*
 * Controller.h - Controls pawns.
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

#ifndef _ADENA_O_CONTROLLER_H_
#define _ADENA_O_CONTROLLER_H_

#include <COObject.h>
#include <Player.h>
#include <IGameServerClient.h>
#include <vector3d.h>

namespace adena
{
namespace game_server
{

	class Controller : public COObject
	{
	public:

		Controller(IOObjectSystem* obj_sys);

		virtual ~Controller();

		virtual void posses(Pawn* pawn);

		// Called when the user sends a moveToLocation packet.
		virtual void clickGround(irr::core::vector3df origin, irr::core::vector3df target, bool mouse_click);

		// Called when the user sends a Action packet.
		virtual void clickObject(Actor* obj, bool shift_click);

		virtual void sendText(irr::core::stringc &msg);

		IGameServerClient* Owner;

		Pawn* OwnedPawn;

		COObject* Target;

	};

}
}

#endif
